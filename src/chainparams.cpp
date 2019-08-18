// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It will only connect to one or two seed nodes because once it connects,
	// it will get a pile of addresses with newer timestamps.
	// Seed nodes are given a random "last seen time" of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xbe;
		pchMessageStart[1] = 0x2a;
		pchMessageStart[2] = 0x53;
		pchMessageStart[3] = 0x6b;
		vAlertPubKey = ParseHex("04445daae44924c1ee1e715629c3254c92c0c06a77716dbbd8551036551f4f23b4d5bff603f064ac5516529d25e4c582e65c484e159503365fb694add9f4cd2334");
		nDefaultPort = 42515;
		nRPCPort = 42516;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);


		const char* pszTimestamp = "start BuySellCoin coin on Sunday 19th of August 2018 12-35-14 AM";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1534245522, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1534245522;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 150507;

		hashGenesisBlock = genesis.GetHash();
  
        LogPrintf("Display genesis %s\n", hashGenesisBlock.ToString().c_str());
	    LogPrintf("Display merkle  %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("Display nonce  %s\n", genesis.nNonce);
        LogPrintf("Display time  %s\n", genesis.nTime);

		assert(genesis.hashMerkleRoot == uint256("0x62a0badc16b3c6bb78842344b0d241c1c81fb7ae9478331aa05eff9656480235"));
		assert(hashGenesisBlock == uint256("0x7c85ab0d795a48bf8bd3ab82904decdbb94ae641198fd812d9a3325199303831"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 26);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 154);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 50);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0", "95.216.33.137"));
		vSeeds.push_back(CDNSSeedData("1", "207.180.245.239"));
		vSeeds.push_back(CDNSSeedData("2", "95.216.38.85"));
		vSeeds.push_back(CDNSSeedData("3", "188.42.33.124"));
		vSeeds.push_back(CDNSSeedData("4", "95.216.38.5"));
		vSeeds.push_back(CDNSSeedData("5", "124.59.73.108"));
		vSeeds.push_back(CDNSSeedData("6", "46.4.178.67"));
		vSeeds.push_back(CDNSSeedData("7", "95.216.125.226"));
		vSeeds.push_back(CDNSSeedData("8", "145.239.39.138"));
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		//strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		//strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		strDarksendPoolDummyAddress = "hFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";
		nLastPOWBlock = 10000000;
		nPOSStartBlock = 5000;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x1d;
		pchMessageStart[1] = 0x7e;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0x2c;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("04445daae44924c1ee1e715629c3254c92c0c06a77716dbbd8551036551f4f23b4d5bff603f064ac5516529d25e4c582e65c484e159503365fb694add9f4cd2334");
		nDefaultPort = 31318;
		nRPCPort = 31319;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 216893;
		genesis.nTime    = 1534245523;

        hashGenesisBlock = genesis.GetHash();

        LogPrintf("Display testNet genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());

		assert(hashGenesisBlock == uint256("0x43abf28608e00e5fa810cdff37c96d48b4c69029454456bba1058c6798519180"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}