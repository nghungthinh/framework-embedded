#include "opendds_if.h"

DDSHandler::DDSHandler()
{
  // Dynamically get the rtps.ini file.
  // char exePath[PATH_MAX];
  // ssize_t len = readlink("/proc/self/exe", exePath, PATH_MAX - 1);
  
  // if (len == -1) {
  //     std::cout << "Error reading the executable path." << std::endl;
  //     exit(EXIT_FAILURE);
  // }
  
  // exePath[len] = '\0'; // Null-terminate the string
  // std::string path(exePath);
  // std::string configPath = path.substr(0, path.find_last_of('/') + 1) + "rtps.ini";

  // const char* argv[] = { "program_name_that_doesnt_matter_here", "-DCPSConfigFile", configPath.c_str() };
  // int argc = sizeof(argv) / sizeof(argv[0]);

  // // Initialize the DomainParticipantFactory
  // dpf_ = TheParticipantFactoryWithArgs(argc, (char**)argv);

  // // Create a DomainParticipant
  // participant_ = createParticipant(dpf_);

  // // Create a Topic
  // topic_ = createTopic(participant_);
}

DDSHandler::~DDSHandler()
{
}
