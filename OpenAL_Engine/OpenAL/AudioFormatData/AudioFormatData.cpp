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

		if (!result)
		{
			Format.CreateFlag = false;
			return Format;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// Žw’è‚µ‚½ƒTƒEƒ“ƒh‚ÌŠK‘w
			auto xmlname = tool.attribute("Name").value();
			if (xmlname == Soundname)
			{
				std::string sub;
				Format.Cue = tool.child("SoundType").child_value("Cue");
				Format.SubGroup = tool.child("SoundType").child_value("SubGroup");
				sub = tool.child("SoundType").child_value("Loop");
				Format.Loopflag = atoi(sub.c_str());
				sub = tool.child("SoundType").child_value("StreamType");
				Format.StreamType = atoi(sub.c_str());

				int maxloop = atoi(tool.attribute("Size").value());

				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{
					SoundInfo info;

					std::string id, maxvol;

					id = soundinfo.child_value("ID");
					info.Extension = soundinfo.child_value("Extension");
					info.SoundName = soundinfo.child_value("SoundName");
					info.MaterialObj = soundinfo.child_value("Material");
					info.Type = soundinfo.child_value("Type");
					maxvol = soundinfo.child_value("MaxVolume");

					info.Id = atoi(id.c_str());
					info.MaxVolume = atof(maxvol.c_str());

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

		if (!result)
		{
			Format.CreateFlag = false;
			return Format;
		}

		xml_node tools = doc.child("SoundList");

		for (xml_node tool = tools.child("SoundData"); tool; tool = tool.next_sibling())
		{
			// Žw’è‚µ‚½ƒTƒEƒ“ƒh‚ÌŠK‘w
			if (tool.attribute("Id").hash_value() == id)
			{
				std::string sub;

				Format.Cue = tool.child("SoundType").child_value("Cue");
				Format.SubGroup = tool.child("SoundType").child_value("SubGroup");
				sub = tool.child("SoundType").child_value("Loop");
				Format.Loopflag = atoi(sub.c_str());
				sub = tool.child("SoundType").child_value("StreamType");
				Format.StreamType = atoi(sub.c_str());

				int maxloop = atoi(tool.attribute("Size").value());

				for (xml_node soundinfo = tool.child("SoundInfo"); soundinfo; soundinfo = soundinfo.next_sibling())
				{
					SoundInfo info;

					std::string id, maxvol;

					id = soundinfo.child_value("ID");
					info.Extension = soundinfo.child_value("Extension");
					info.SoundName = soundinfo.child_value("SoundName");
					info.MaterialObj = soundinfo.child_value("Material");
					info.Type = soundinfo.child_value("Type");
					maxvol = soundinfo.child_value("MaxVolume");

					info.Id = atoi(id.c_str());
					info.MaxVolume = atof(maxvol.c_str());

					Format.Soundinfo.push_back(info);
				}

			}
		}
		Format.CreateFlag = true;
		return Format;

	}
}