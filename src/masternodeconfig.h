<<<<<<< HEAD

// Copyright (c) 2014-2017 The GelCoin developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2012 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SRC_MASTERNODECONFIG_H_
#define SRC_MASTERNODECONFIG_H_

<<<<<<< HEAD
=======
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class CMasternodeConfig;
extern CMasternodeConfig masternodeConfig;

class CMasternodeConfig
{

public:
<<<<<<< HEAD

    class CMasternodeEntry {

    private:
        std::string alias;
        std::string ip;
        std::string privKey;
        std::string txHash;
        std::string outputIndex;
    public:

        CMasternodeEntry(std::string alias, std::string ip, std::string privKey, std::string txHash, std::string outputIndex) {
            this->alias = alias;
            this->ip = ip;
            this->privKey = privKey;
            this->txHash = txHash;
            this->outputIndex = outputIndex;
        }

        const std::string& getAlias() const {
            return alias;
        }

        void setAlias(const std::string& alias) {
            this->alias = alias;
        }

        const std::string& getOutputIndex() const {
            return outputIndex;
        }

        void setOutputIndex(const std::string& outputIndex) {
            this->outputIndex = outputIndex;
        }

        const std::string& getPrivKey() const {
            return privKey;
        }

        void setPrivKey(const std::string& privKey) {
            this->privKey = privKey;
        }

        const std::string& getTxHash() const {
            return txHash;
        }

        void setTxHash(const std::string& txHash) {
            this->txHash = txHash;
        }

        const std::string& getIp() const {
            return ip;
        }

        void setIp(const std::string& ip) {
            this->ip = ip;
        }
    };

    CMasternodeConfig() {
        entries = std::vector<CMasternodeEntry>();
    }

    void clear();
    bool read(std::string& strErr);
    void add(std::string alias, std::string ip, std::string privKey, std::string txHash, std::string outputIndex);

    std::vector<CMasternodeEntry>& getEntries() {
        return entries;
    }

    int getCount() {
        return (int)entries.size();
    }

private:
    std::vector<CMasternodeEntry> entries;


=======
	class CMasternodeEntry {

	private:
		std::string alias;
		std::string ip;
		std::string privKey;
		std::string txHash;
		std::string outputIndex;

	public:

		CMasternodeEntry(std::string alias, std::string ip, std::string privKey, std::string txHash, std::string outputIndex) {
			this->alias = alias;
			this->ip = ip;
			this->privKey = privKey;
			this->txHash = txHash;
			this->outputIndex = outputIndex;
		}

		const std::string& getAlias() const {
			return alias;
		}

		void setAlias(const std::string& alias) {
			this->alias = alias;
		}

		const std::string& getOutputIndex() const {
			return outputIndex;
		}

		void setOutputIndex(const std::string& outputIndex) {
			this->outputIndex = outputIndex;
		}

		const std::string& getPrivKey() const {
			return privKey;
		}

		void setPrivKey(const std::string& privKey) {
			this->privKey = privKey;
		}

		const std::string& getTxHash() const {
			return txHash;
		}

		void setTxHash(const std::string& txHash) {
			this->txHash = txHash;
		}

		const std::string& getIp() const {
			return ip;
		}

		void setIp(const std::string& ip) {
			this->ip = ip;
		}
	};

	CMasternodeConfig() {
		entries = std::vector<CMasternodeEntry>();
	}

	void clear();
    bool read(boost::filesystem::path path);
	void add(std::string alias, std::string ip, std::string privKey, std::string txHash, std::string outputIndex);

	std::vector<CMasternodeEntry>& getEntries() {
		return entries;
	}

	int getCount()
	{
		int c = -1;
		BOOST_FOREACH (CMasternodeEntry e, entries) {
						if (e.getAlias() != "") c++;
					}
		return c;
	}

private:
	std::vector<CMasternodeEntry> entries;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};


#endif /* SRC_MASTERNODECONFIG_H_ */
<<<<<<< HEAD
=======

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
