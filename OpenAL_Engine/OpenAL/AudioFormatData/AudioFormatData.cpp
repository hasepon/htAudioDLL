#include "AudioFormatData.h"

#include <codecvt>
namespace htAudio {

	AudioFormatData::AudioFormatData()
	{
	}


	AudioFormatData::~AudioFormatData()
	{

	}

	SoundType AudioFormatData::GetAudioFormatData(std::string filepath, std::string Soundname)
	{
		using namespace pugi;

		SoundType Format;
		xml_document doc;
		filepath += "\\Xml\\SoundList.xml";

		xml_parse_result result;
		Format.CreateFlag = false;

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			Format.CreateFlag = false;
			return Format;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// w’è‚µ‚½ƒTƒEƒ“ƒh‚ÌŠK‘w
			auto xmlname = tool.attribute("Name").value();
			if (xmlname == Soundname)
			{
				Format.DataID = (int)tool.attribute("ID").hash_value();
				Format.Cue = tool.child("SoundType").child_value("Cue");
				Format.SubGroup = tool.child("SoundType").child_value("SubGroup");
				Format.Loopflag = atoi(tool.child("SoundType").child_value("Loop"));
				Format.StreamType = atoi(tool.child("SoundType").child_value("StreamType"));
				Format.b3DAudio = atoi(tool.child("SoundType").child_value("SurroundFlag"));

				int maxloop = atoi(tool.attribute("Size").value());

				if (Format.b3DAudio == 1)
				{
					xml_node soundinfo = tool.child("SurroundInfo");
					Format.Sorrundinfo.OuterGain = atof(soundinfo.child_value("OuterGain"));
					Format.Sorrundinfo.OuterAngle = atof(soundinfo.child_value("OuterAngle"));
					Format.Sorrundinfo.innerAngle = atof(soundinfo.child_value("InnerAngle"));
				}

				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{
					SoundInfo info;

					std::string id, maxvol;

					info.Id = atoi(soundinfo.child_value("ID"));
					info.Extension = soundinfo.child_value("Extension");
					info.SoundName = soundinfo.child_value("SoundName");
					info.MaterialObj = soundinfo.child_value("Material");
					info.Type = soundinfo.child_value("Type");
					info.LowVolume = atof(soundinfo.child_value("LowVolume"));
					info.DefaultVolume = atof(soundinfo.child_value("DefaultVolume"));
					info.MaxVolume = atof(soundinfo.child_value("MaxVolume"));

					Format.Soundinfo.push_back(info);
				}

			}
		}
		Format.CreateFlag = true;
		return Format;
	}


	SoundType AudioFormatData::GetAudioFormatData(std::string filepath, int id)
	{
		using namespace pugi;

		SoundType Format;
		xml_document doc;

		Format.CreateFlag = false;
		xml_parse_result result;

		filepath += "\\Xml\\SoundList.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			Format.CreateFlag = false;
			return Format;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// w’è‚µ‚½ƒTƒEƒ“ƒh‚ÌŠK‘w
			if (tool.attribute("Id").hash_value() == id)
			{
				std::string sub;
				Format.DataID = id;
				Format.Cue = tool.child("SoundType").child_value("Cue");
				Format.SubGroup = tool.child("SoundType").child_value("SubGroup");
				sub = tool.child("SoundType").child_value("Loop");
				Format.Loopflag = atoi(sub.c_str());
				sub = tool.child("SoundType").child_value("StreamType");
				Format.StreamType = atoi(sub.c_str());
				Format.b3DAudio = atoi(tool.child("SoundType").child_value("SurroundFlag"));

				int maxloop = atoi(tool.attribute("Size").value());


				if (Format.b3DAudio == 1)
				{
					xml_node soundinfo = tool.child("SurroundInfo");
					Format.Sorrundinfo.OuterGain = atof(soundinfo.child_value("OuterGain"));
					Format.Sorrundinfo.OuterAngle = atof(soundinfo.child_value("OuterAngle"));
					Format.Sorrundinfo.innerAngle = atof(soundinfo.child_value("InnerAngle"));
				}

				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{

					SoundInfo info;

					std::string id, maxvol;

					info.Id = atoi(soundinfo.child_value("ID"));
					info.Extension = soundinfo.child_value("Extension");
					info.SoundName = soundinfo.child_value("SoundName");
					info.MaterialObj = soundinfo.child_value("Material");
					info.Type = soundinfo.child_value("Type");
					info.LowVolume = atof(soundinfo.child_value("LowVolume"));
					info.DefaultVolume = atof(soundinfo.child_value("DefaultVolume"));
					info.MaxVolume = atof(soundinfo.child_value("MaxVolume"));

					Format.Soundinfo.push_back(info);
				}


			}
		}
		Format.CreateFlag = true;
		return Format;

	}

	void AudioFormatData::WriteAudioFormatData(std::string filepath, SoundType registinfo)
	{
		using namespace pugi;

		xml_document doc;

		xml_parse_result result;

		filepath += "\\Xml\\SoundList.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (result == false)
		{
			return;
		}

		xml_node tools = doc.child("SoundList");
		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			if (tool.attribute("Id").hash_value() == registinfo.DataID)
			{
				if (registinfo.b3DAudio == 0)
					continue;
				xml_node soundinfo = tool.child("SurroundInfo");
				char buf[24];

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.OuterGain);
				soundinfo.child("OuterGain").set_value(buf);

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.OuterAngle);
				soundinfo.child("OuterAngle").set_value(buf);

				snprintf(buf, 24, "%f", registinfo.Sorrundinfo.innerAngle);
				soundinfo.child("InnerAngle").set_value(buf);
			}
		}

	}

	bool AudioFormatData::ReadListenerState(ListenerStates* state, std::string filepath)
	{
		using namespace pugi;
		xml_document doc;
		xml_parse_result result;

		filepath += "\\Xml\\ListenerState.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (!result)
		{
			return false;
		}

		xml_node tools = doc.child("ListenerState");
		xml_node tool = tools.child("State");

		state->OuterGain  = (float)atof(tool.child_value("ConeQuterGain"));
		state->InnerAngle = (float)atof(tool.child_value("ConeInnerAngle"));
		state->OuterAngle = (float)atof(tool.child_value("ConeOuterAngle"));

		return true;
	}

	bool AudioFormatData::WriteListenerState(ListenerStates state, std::string filepath)
	{
		using namespace pugi;
		xml_document doc;
		xml_parse_result result;

		filepath += "\\Xml\\ListenerState.xml";

		result = doc.load_file(filepath.c_str(), parse_default | parse_pi);

		if (!result)
		{
			return false;
		}

		xml_node tools = doc.child("ListenerState");
		xml_node tool = tools.child("State");

		// “o˜^—p‚Ì•Ï””z—ñ
		char buf[24];

		snprintf(buf,24,"%f",state.OuterGain);
		tool.child("ConeQuterGain").set_value(buf);

		snprintf(buf, 24, "%f", state.InnerAngle);
		tool.child("ConeInnerAngle").set_value(buf);

		snprintf(buf, 24, "%f", state.OuterAngle);
		tool.child("ConeOuterAngle").set_value(buf);
		
		return true;
	}

}