<<<<<<< HEAD

#include "netbase.h"
=======
#include "net.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "masternodeconfig.h"
#include "util.h"
#include "chainparams.h"

<<<<<<< HEAD
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
CMasternodeConfig masternodeConfig;

void CMasternodeConfig::add(std::string alias, std::string ip, std::string privKey, std::string txHash, std::string outputIndex) {
    CMasternodeEntry cme(alias, ip, privKey, txHash, outputIndex);
    entries.push_back(cme);
}

<<<<<<< HEAD
bool CMasternodeConfig::read(std::string& strErr) {
    int linenumber = 1;
    boost::filesystem::path pathMasternodeConfigFile = GetMasternodeConfigFile();
    boost::filesystem::ifstream streamConfig(pathMasternodeConfigFile);

    if (!streamConfig.good()) {
        FILE* configFile = fopen(pathMasternodeConfigFile.string().c_str(), "a");
        if (configFile != NULL) {
            std::string strHeader = "# Masternode config file\n"
                          "# Format: alias IP:port masternodeprivkey collateral_output_txid collateral_output_index\n"
                          "# Example: mn1 127.0.0.2:19999 93HaYBVUCYjEMeeH1Y4sBGLALQZE1Yc1K64xiqgX37tGBDQL8Xg 2bcd3c84c84f87eaa86e4e56834c92927a07f9e18718810b92e0d0324456a67c 0\n";
            fwrite(strHeader.c_str(), std::strlen(strHeader.c_str()), 1, configFile);
            fclose(configFile);
        }
        return true; // Nothing to read, so just return
    }

    for(std::string line; std::getline(streamConfig, line); linenumber++)
    {
        if(line.empty()) continue;

        std::istringstream iss(line);
        std::string comment, alias, ip, privKey, txHash, outputIndex;

        if (iss >> comment) {
            if(comment.at(0) == '#') continue;
            iss.str(line);
            iss.clear();
        }

        if (!(iss >> alias >> ip >> privKey >> txHash >> outputIndex)) {
            iss.str(line);
            iss.clear();
            if (!(iss >> alias >> ip >> privKey >> txHash >> outputIndex)) {
                strErr = _("Could not parse masternode.conf") + "\n" +
                        strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"";
                streamConfig.close();
                return false;
            }
        }

        int port = 0;
        std::string hostname = "";
        SplitHostPort(ip, port, hostname);
        if(port == 0 || hostname == "") {
            strErr = _("Failed to parse host:port string") + "\n"+
                    strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"";
            streamConfig.close();
            return false;
        }
        int mainnetDefaultPort = Params(CBaseChainParams::MAIN).GetDefaultPort();
        if(Params().NetworkIDString() == CBaseChainParams::MAIN) {
            if(port != mainnetDefaultPort) {
                strErr = _("Invalid port detected in masternode.conf") + "\n" +
                        strprintf(_("Port: %d"), port) + "\n" +
                        strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"" + "\n" +
                        strprintf(_("(must be %d for mainnet)"), mainnetDefaultPort);
                streamConfig.close();
                return false;
            }
        } else if(port == mainnetDefaultPort) {
            strErr = _("Invalid port detected in masternode.conf") + "\n" +
                    strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"" + "\n" +
                    strprintf(_("(%d could be used only on mainnet)"), mainnetDefaultPort);
=======
bool CMasternodeConfig::read(boost::filesystem::path path) {
    boost::filesystem::ifstream streamConfig(GetMasternodeConfigFile());
    if (!streamConfig.good()) {
        return true; // No masternode.conf file is OK
    }

    for (std::string line; std::getline(streamConfig, line); ) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string alias, ip, privKey, txHash, outputIndex;
        if (!(iss >> alias >> ip >> privKey >> txHash >> outputIndex)) {
            if (alias.substr(0,1) == "#") continue;
            LogPrintf("CMasternodeConfig::read - Could not parse masternode.conf. Line: %s\n", line);
            streamConfig.close();
            return false;
        }

        if (Params().NetworkID() == CBaseChainParams::MAIN) {
            if(CService(ip).GetPort() != 28666) {
                LogPrintf("Invalid port detected in masternode.conf: %s (must be 17170 for mainnet)\n", line.c_str());
                streamConfig.close();
                return false;
            }
        } else if(CService(ip).GetPort() == 28666) {
            LogPrintf("Invalid port detected in masternode.conf: %s (17170 must be only on mainnet)\n", line.c_str());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            streamConfig.close();
            return false;
        }

<<<<<<< HEAD
=======
        if (!(CService(ip).IsIPv4() && CService(ip).IsRoutable())) {
            LogPrintf("Invalid Address detected in masternode.conf: %s (IPV4 ONLY) \n", line.c_str());
            streamConfig.close();
            return false;
        }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        add(alias, ip, privKey, txHash, outputIndex);
    }

<<<<<<< HEAD
    streamConfig.close();
    return true;
=======
    return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
