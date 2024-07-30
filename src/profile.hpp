#pragma once

#include <map>
#include <vector>
#include <string>

#define DEFAULT_PROFILE "default"

// Target files to be replaced
const std::vector<std::string> TARGET_NAMES {"CCGameManager.dat", "CCGameManager2.dat", "CCLocalLevels.dat", "CCLocalLevels2.dat"};

/** Displayable name and HTTPS address */
struct StringPair {
	std::string mName;
	std::string mURL;
};

/* ID and StringPair for saving */
struct ProfileInfo {
	std::string id;
	StringPair pair;
};

/** Defines the name and URL of the server */
extern std::map<std::string, StringPair> profiles;
extern std::vector<ProfileInfo> customProfiles;

extern std::string activeProfile;

void loadProfiles();
void saveProfiles();
