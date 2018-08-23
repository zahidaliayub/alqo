// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers// Copyright (c) 2017-2018 The ALQO & Bitfineon developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000006680a85db563f3a849c77e02a8c860068474ab2c5495cc24a2204727b62"))
	(225000, uint256("0x0000000000001121808b217485fb774b79e06c528254ada7b06473a7da4a7c8b"))
	(225001, uint256("0x0000000000001f44d85b8f2b5ead0630f2796cb2d26017f79b7a0221d17d4da2"))
	(225020, uint256("0x0000000000016246ac12933f8afa593f1846ba468a6bdc0c85e40c19b9b0ccca"))
	(225040, uint256("0x0000000000022a323903976c5d4bf0fc3434922dad1f6e30804ac40b2117ac25"))
	(225200, uint256("0x000000000000447aace641e9e58af4f4b94336e10cf945cdb28479cd262db059"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1523809869, // * UNIX timestamp of last checkpoint block
    1157185,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x94;
        pchMessageStart[1] = 0x04;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x14;
        vAlertPubKey = ParseHex("0497dfcea626dca270cfe2eebf1160733b07352af966926e30058ca53dae05bbc71d64dbaa0c66e373211e324a23b361fc33e1e2dece1fb90afcefc707643a28f5");
        nDefaultPort = 55500;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // ALQO starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ALQO: 1 day
        nTargetSpacing = 1 * 60;  // ALQO: 1 minute
        nMaturity = 29;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;
		strDeveloperFeePayee = "AG6MCBRozzcQMMi2SXdi4TJhhLeycQERyk";
		
        /** Height or Time Based Activations **/
        nLastPOWBlock = 408960;
        nModifierUpdateBlock = 615800;
        nZerocoinStartHeight = 1000000;
        nZerocoinStartTime = 1577836800;
        nBlockEnforceSerialRange = 1000000; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1000000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 1000000; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1000000; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 1000000; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
		
        nEnforceNewSporkKey = 1525158000; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1527811200; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        const char* pszTimestamp = "30th October 2017 - ALQO - The day you'll remember.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040fbf75ea45bf7eb65f9075e8342b7520d077b66f964e9b1963c96cefd9a2c52e93d0def918e0cd3c91f42821f429b2be4505552dede31c96f95f0d843da0beae") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1509321601;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 46765;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006680a85db563f3a849c77e02a8c860068474ab2c5495cc24a2204727b62"));
        assert(genesis.hashMerkleRoot == uint256("0xb832a1d306b8e5b7feeb7f57ad908f6e93b89be00048393c923542036e135377"));

        vSeeds.push_back(CDNSSeedData("mainseed.alqoseednodes.org", "mainseed.alqoseednodes.org"));
        vSeeds.push_back(CDNSSeedData("mainseed2.alqoseednodes.org", "mainseed2.alqoseednodes.org"));
        vSeeds.push_back(CDNSSeedData("85.25.138.64", "85.25.138.64"));

		vSeeds.push_back(CDNSSeedData("198.199.119.77", "198.199.119.77"));
		vSeeds.push_back(CDNSSeedData("195.181.243.147", "195.181.243.147"));
		vSeeds.push_back(CDNSSeedData("144.202.65.112", "144.202.65.112"));
		vSeeds.push_back(CDNSSeedData("80.208.224.238", "80.208.224.238"));
		vSeeds.push_back(CDNSSeedData("107.173.240.226", "107.173.240.226"));
		vSeeds.push_back(CDNSSeedData("89.47.166.72", "89.47.166.72"));
		vSeeds.push_back(CDNSSeedData("94.177.203.102", "94.177.203.102"));
		vSeeds.push_back(CDNSSeedData("5.249.151.122", "5.249.151.122"));
		vSeeds.push_back(CDNSSeedData("108.61.220.88", "108.61.220.88"));
		vSeeds.push_back(CDNSSeedData("199.247.9.95", "199.247.9.95"));
		vSeeds.push_back(CDNSSeedData("62.77.158.199", "62.77.158.199"));
		vSeeds.push_back(CDNSSeedData("149.28.110.82", "149.28.110.82"));
		vSeeds.push_back(CDNSSeedData("176.223.139.9", "176.223.139.9"));
		vSeeds.push_back(CDNSSeedData("212.24.110.226", "212.24.110.226"));
		vSeeds.push_back(CDNSSeedData("176.223.134.100", "176.223.134.100"));
		vSeeds.push_back(CDNSSeedData("144.202.22.56", "144.202.22.56"));
		vSeeds.push_back(CDNSSeedData("80.211.30.165", "80.211.30.165"));
		vSeeds.push_back(CDNSSeedData("51.15.251.212", "51.15.251.212"));
		vSeeds.push_back(CDNSSeedData("89.40.12.143", "89.40.12.143"));
		vSeeds.push_back(CDNSSeedData("89.40.5.53", "89.40.5.53"));
		vSeeds.push_back(CDNSSeedData("45.63.21.121", "45.63.21.121"));
		vSeeds.push_back(CDNSSeedData("92.222.91.228", "92.222.91.228"));
		vSeeds.push_back(CDNSSeedData("80.208.231.246", "80.208.231.246"));
		vSeeds.push_back(CDNSSeedData("176.223.131.166", "176.223.131.166"));
		vSeeds.push_back(CDNSSeedData("89.40.3.86", "89.40.3.86"));
		vSeeds.push_back(CDNSSeedData("209.250.238.206", "209.250.238.206"));
		vSeeds.push_back(CDNSSeedData("136.144.171.72", "136.144.171.72"));
		vSeeds.push_back(CDNSSeedData("208.167.248.149", "208.167.248.149"));
		vSeeds.push_back(CDNSSeedData("80.208.229.15", "80.208.229.15"));
		vSeeds.push_back(CDNSSeedData("75.127.13.84", "75.127.13.84"));
		vSeeds.push_back(CDNSSeedData("176.223.134.41", "176.223.134.41"));
		vSeeds.push_back(CDNSSeedData("199.247.0.142", "199.247.0.142"));
		vSeeds.push_back(CDNSSeedData("176.223.129.83", "176.223.129.83"));
		vSeeds.push_back(CDNSSeedData("45.32.109.181", "45.32.109.181"));
		vSeeds.push_back(CDNSSeedData("199.247.12.162", "199.247.12.162"));
		vSeeds.push_back(CDNSSeedData("62.77.158.110", "62.77.158.110"));
		vSeeds.push_back(CDNSSeedData("62.77.157.56", "62.77.157.56"));
		vSeeds.push_back(CDNSSeedData("80.209.230.100", "80.209.230.100"));
		vSeeds.push_back(CDNSSeedData("46.101.230.74", "46.101.230.74"));
		vSeeds.push_back(CDNSSeedData("82.223.43.175", "82.223.43.175"));
		vSeeds.push_back(CDNSSeedData("209.250.236.227", "209.250.236.227"));
		vSeeds.push_back(CDNSSeedData("80.208.225.51", "80.208.225.51"));
		vSeeds.push_back(CDNSSeedData("89.40.4.25", "89.40.4.25"));
		vSeeds.push_back(CDNSSeedData("89.40.3.89", "89.40.3.89"));
		vSeeds.push_back(CDNSSeedData("142.44.194.77", "142.44.194.77"));
		vSeeds.push_back(CDNSSeedData("104.238.141.180", "104.238.141.180"));
		vSeeds.push_back(CDNSSeedData("151.80.174.124", "151.80.174.124"));
		vSeeds.push_back(CDNSSeedData("95.179.128.248", "95.179.128.248"));
		vSeeds.push_back(CDNSSeedData("89.40.14.13", "89.40.14.13"));
		vSeeds.push_back(CDNSSeedData("45.76.136.57", "45.76.136.57"));
		vSeeds.push_back(CDNSSeedData("80.211.211.74", "80.211.211.74"));
		vSeeds.push_back(CDNSSeedData("148.163.92.132", "148.163.92.132"));
		vSeeds.push_back(CDNSSeedData("176.223.142.55", "176.223.142.55"));
		vSeeds.push_back(CDNSSeedData("62.77.159.138", "62.77.159.138"));
		vSeeds.push_back(CDNSSeedData("104.238.185.123", "104.238.185.123"));
		vSeeds.push_back(CDNSSeedData("89.40.0.250", "89.40.0.250"));
		vSeeds.push_back(CDNSSeedData("89.40.14.9", "89.40.14.9"));
		vSeeds.push_back(CDNSSeedData("109.235.67.200", "109.235.67.200"));
		vSeeds.push_back(CDNSSeedData("80.208.230.34", "80.208.230.34"));
		vSeeds.push_back(CDNSSeedData("54.196.164.31", "54.196.164.31"));
		vSeeds.push_back(CDNSSeedData("89.47.160.104", "89.47.160.104"));
		vSeeds.push_back(CDNSSeedData("62.77.158.172", "62.77.158.172"));
		vSeeds.push_back(CDNSSeedData("89.40.15.38", "89.40.15.38"));
		vSeeds.push_back(CDNSSeedData("80.209.233.43", "80.209.233.43"));
		vSeeds.push_back(CDNSSeedData("62.77.155.205", "62.77.155.205"));
		vSeeds.push_back(CDNSSeedData("207.148.8.231", "207.148.8.231"));
		vSeeds.push_back(CDNSSeedData("80.211.65.19", "80.211.65.19"));
		vSeeds.push_back(CDNSSeedData("80.208.227.222", "80.208.227.222"));
		vSeeds.push_back(CDNSSeedData("39.104.56.56", "39.104.56.56"));
		vSeeds.push_back(CDNSSeedData("199.247.20.209", "199.247.20.209"));
		vSeeds.push_back(CDNSSeedData("138.197.191.206", "138.197.191.206"));
		vSeeds.push_back(CDNSSeedData("108.61.197.233", "108.61.197.233"));
		vSeeds.push_back(CDNSSeedData("217.69.12.52", "217.69.12.52"));
		vSeeds.push_back(CDNSSeedData("80.209.236.27", "80.209.236.27"));
		vSeeds.push_back(CDNSSeedData("207.246.83.165", "207.246.83.165"));
		vSeeds.push_back(CDNSSeedData("80.240.27.131", "80.240.27.131"));
		vSeeds.push_back(CDNSSeedData("107.174.245.39", "107.174.245.39"));
		vSeeds.push_back(CDNSSeedData("212.237.11.175", "212.237.11.175"));
		vSeeds.push_back(CDNSSeedData("163.172.133.152", "163.172.133.152"));
		vSeeds.push_back(CDNSSeedData("108.61.241.133", "108.61.241.133"));
		vSeeds.push_back(CDNSSeedData("149.28.35.242", "149.28.35.242"));
		vSeeds.push_back(CDNSSeedData("208.167.248.144", "208.167.248.144"));
		vSeeds.push_back(CDNSSeedData("107.174.245.120", "107.174.245.120"));
		vSeeds.push_back(CDNSSeedData("45.76.46.204", "45.76.46.204"));
		vSeeds.push_back(CDNSSeedData("89.40.8.77", "89.40.8.77"));
		vSeeds.push_back(CDNSSeedData("45.77.45.37", "45.77.45.37"));
		vSeeds.push_back(CDNSSeedData("209.250.233.54", "209.250.233.54"));
		vSeeds.push_back(CDNSSeedData("45.32.84.79", "45.32.84.79"));
		vSeeds.push_back(CDNSSeedData("89.47.160.86", "89.47.160.86"));
		vSeeds.push_back(CDNSSeedData("35.200.132.197", "35.200.132.197"));
		vSeeds.push_back(CDNSSeedData("45.76.63.125", "45.76.63.125"));
		vSeeds.push_back(CDNSSeedData("95.179.137.120", "95.179.137.120"));
		vSeeds.push_back(CDNSSeedData("45.32.90.193", "45.32.90.193"));
		vSeeds.push_back(CDNSSeedData("176.223.139.218", "176.223.139.218"));
		vSeeds.push_back(CDNSSeedData("209.250.241.15", "209.250.241.15"));
		vSeeds.push_back(CDNSSeedData("45.77.121.25", "45.77.121.25"));
		vSeeds.push_back(CDNSSeedData("45.76.218.68", "45.76.218.68"));
		vSeeds.push_back(CDNSSeedData("212.24.103.41", "212.24.103.41"));
		vSeeds.push_back(CDNSSeedData("46.38.253.46", "46.38.253.46"));
		vSeeds.push_back(CDNSSeedData("194.135.82.5", "194.135.82.5"));
		vSeeds.push_back(CDNSSeedData("62.77.153.173", "62.77.153.173"));
		vSeeds.push_back(CDNSSeedData("45.77.149.46", "45.77.149.46"));
		vSeeds.push_back(CDNSSeedData("173.255.247.147", "173.255.247.147"));
		vSeeds.push_back(CDNSSeedData("176.223.133.13", "176.223.133.13"));
		vSeeds.push_back(CDNSSeedData("47.92.33.126", "47.92.33.126"));
		vSeeds.push_back(CDNSSeedData("45.77.229.0", "45.77.229.0"));
		vSeeds.push_back(CDNSSeedData("212.24.109.232", "212.24.109.232"));
		vSeeds.push_back(CDNSSeedData("217.163.29.231", "217.163.29.231"));
		vSeeds.push_back(CDNSSeedData("89.40.8.72", "89.40.8.72"));
		vSeeds.push_back(CDNSSeedData("108.58.17.155", "108.58.17.155"));
		vSeeds.push_back(CDNSSeedData("89.40.2.58", "89.40.2.58"));
		vSeeds.push_back(CDNSSeedData("45.77.200.47", "45.77.200.47"));
		vSeeds.push_back(CDNSSeedData("62.77.153.157", "62.77.153.157"));
		vSeeds.push_back(CDNSSeedData("144.202.103.236", "144.202.103.236"));
		vSeeds.push_back(CDNSSeedData("89.47.160.11", "89.47.160.11"));
		vSeeds.push_back(CDNSSeedData("140.82.56.126", "140.82.56.126"));
		vSeeds.push_back(CDNSSeedData("89.47.160.98", "89.47.160.98"));
		vSeeds.push_back(CDNSSeedData("89.47.160.78", "89.47.160.78"));
		vSeeds.push_back(CDNSSeedData("54.147.248.241", "54.147.248.241"));
		vSeeds.push_back(CDNSSeedData("199.247.1.53", "199.247.1.53"));
		vSeeds.push_back(CDNSSeedData("80.240.24.163", "80.240.24.163"));
		vSeeds.push_back(CDNSSeedData("62.77.157.14", "62.77.157.14"));
		vSeeds.push_back(CDNSSeedData("80.209.230.96", "80.209.230.96"));
		vSeeds.push_back(CDNSSeedData("80.208.224.27", "80.208.224.27"));
		vSeeds.push_back(CDNSSeedData("45.76.227.188", "45.76.227.188"));
		vSeeds.push_back(CDNSSeedData("62.77.159.139", "62.77.159.139"));
		vSeeds.push_back(CDNSSeedData("50.116.62.5", "50.116.62.5"));
		vSeeds.push_back(CDNSSeedData("198.211.114.139", "198.211.114.139"));
		vSeeds.push_back(CDNSSeedData("176.223.130.219", "176.223.130.219"));
		vSeeds.push_back(CDNSSeedData("194.135.81.93", "194.135.81.93"));
		vSeeds.push_back(CDNSSeedData("80.209.230.20", "80.209.230.20"));
		vSeeds.push_back(CDNSSeedData("89.40.2.75", "89.40.2.75"));
		vSeeds.push_back(CDNSSeedData("104.207.142.114", "104.207.142.114"));
		vSeeds.push_back(CDNSSeedData("207.246.91.175", "207.246.91.175"));
		vSeeds.push_back(CDNSSeedData("185.204.216.61", "185.204.216.61"));
		vSeeds.push_back(CDNSSeedData("176.223.139.11", "176.223.139.11"));
		vSeeds.push_back(CDNSSeedData("54.68.152.17", "54.68.152.17"));
		vSeeds.push_back(CDNSSeedData("62.77.158.32", "62.77.158.32"));
		vSeeds.push_back(CDNSSeedData("149.28.164.217", "149.28.164.217"));
		vSeeds.push_back(CDNSSeedData("47.92.164.169", "47.92.164.169"));
		vSeeds.push_back(CDNSSeedData("89.47.167.0", "89.47.167.0"));
		vSeeds.push_back(CDNSSeedData("45.32.165.86", "45.32.165.86"));
		vSeeds.push_back(CDNSSeedData("47.92.74.129", "47.92.74.129"));
		vSeeds.push_back(CDNSSeedData("176.223.133.131", "176.223.133.131"));
		vSeeds.push_back(CDNSSeedData("144.202.25.39", "144.202.25.39"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("144.202.85.182", "144.202.85.182"));
		vSeeds.push_back(CDNSSeedData("45.77.230.68", "45.77.230.68"));
		vSeeds.push_back(CDNSSeedData("86.121.208.47", "86.121.208.47"));
		vSeeds.push_back(CDNSSeedData("144.202.24.45", "144.202.24.45"));
		vSeeds.push_back(CDNSSeedData("195.181.241.220", "195.181.241.220"));
		vSeeds.push_back(CDNSSeedData("80.209.237.187", "80.209.237.187"));
		vSeeds.push_back(CDNSSeedData("198.13.46.221", "198.13.46.221"));
		vSeeds.push_back(CDNSSeedData("62.77.156.219", "62.77.156.219"));
		vSeeds.push_back(CDNSSeedData("125.253.112.169", "125.253.112.169"));
		vSeeds.push_back(CDNSSeedData("45.32.225.226", "45.32.225.226"));
		vSeeds.push_back(CDNSSeedData("45.76.244.186", "45.76.244.186"));
		vSeeds.push_back(CDNSSeedData("80.208.229.215", "80.208.229.215"));
		vSeeds.push_back(CDNSSeedData("142.44.194.178", "142.44.194.178"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("176.223.131.95", "176.223.131.95"));
		vSeeds.push_back(CDNSSeedData("195.181.242.183", "195.181.242.183"));
		vSeeds.push_back(CDNSSeedData("149.28.197.158", "149.28.197.158"));
		vSeeds.push_back(CDNSSeedData("39.104.114.150", "39.104.114.150"));
		vSeeds.push_back(CDNSSeedData("45.77.201.188", "45.77.201.188"));
		vSeeds.push_back(CDNSSeedData("174.138.16.180", "174.138.16.180"));
		vSeeds.push_back(CDNSSeedData("178.33.75.156", "178.33.75.156"));
		vSeeds.push_back(CDNSSeedData("193.192.252.50", "193.192.252.50"));
		vSeeds.push_back(CDNSSeedData("63.142.252.46", "63.142.252.46"));
		vSeeds.push_back(CDNSSeedData("89.40.13.63", "89.40.13.63"));
		vSeeds.push_back(CDNSSeedData("23.239.24.5", "23.239.24.5"));
		vSeeds.push_back(CDNSSeedData("94.139.9.80", "94.139.9.80"));
		vSeeds.push_back(CDNSSeedData("185.69.53.225", "185.69.53.225"));
		vSeeds.push_back(CDNSSeedData("89.40.2.32", "89.40.2.32"));
		vSeeds.push_back(CDNSSeedData("46.38.241.37", "46.38.241.37"));
		vSeeds.push_back(CDNSSeedData("192.99.25.246", "192.99.25.246"));
		vSeeds.push_back(CDNSSeedData("89.40.7.181", "89.40.7.181"));
		vSeeds.push_back(CDNSSeedData("62.77.159.60", "62.77.159.60"));
		vSeeds.push_back(CDNSSeedData("94.176.237.148", "94.176.237.148"));
		vSeeds.push_back(CDNSSeedData("45.76.92.21", "45.76.92.21"));
		vSeeds.push_back(CDNSSeedData("80.211.156.142", "80.211.156.142"));
		vSeeds.push_back(CDNSSeedData("45.32.146.148", "45.32.146.148"));
		vSeeds.push_back(CDNSSeedData("62.77.155.114", "62.77.155.114"));
		vSeeds.push_back(CDNSSeedData("79.98.25.58", "79.98.25.58"));
		vSeeds.push_back(CDNSSeedData("38.127.169.147", "38.127.169.147"));
		vSeeds.push_back(CDNSSeedData("176.223.131.247", "176.223.131.247"));
		vSeeds.push_back(CDNSSeedData("199.247.4.224", "199.247.4.224"));
		vSeeds.push_back(CDNSSeedData("104.225.220.153", "104.225.220.153"));
		vSeeds.push_back(CDNSSeedData("159.65.148.202", "159.65.148.202"));
		vSeeds.push_back(CDNSSeedData("140.82.62.30", "140.82.62.30"));
		vSeeds.push_back(CDNSSeedData("89.40.0.251", "89.40.0.251"));
		vSeeds.push_back(CDNSSeedData("212.24.100.157", "212.24.100.157"));
		vSeeds.push_back(CDNSSeedData("89.40.8.69", "89.40.8.69"));
		vSeeds.push_back(CDNSSeedData("108.61.205.160", "108.61.205.160"));
		vSeeds.push_back(CDNSSeedData("62.77.152.141", "62.77.152.141"));
		vSeeds.push_back(CDNSSeedData("176.223.130.163", "176.223.130.163"));
		vSeeds.push_back(CDNSSeedData("37.25.104.18", "37.25.104.18"));
		vSeeds.push_back(CDNSSeedData("209.250.230.132", "209.250.230.132"));
		vSeeds.push_back(CDNSSeedData("198.13.46.96", "198.13.46.96"));
		vSeeds.push_back(CDNSSeedData("89.40.3.91", "89.40.3.91"));
		vSeeds.push_back(CDNSSeedData("89.40.3.220", "89.40.3.220"));
		vSeeds.push_back(CDNSSeedData("62.77.157.18", "62.77.157.18"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("45.76.95.233", "45.76.95.233"));
		vSeeds.push_back(CDNSSeedData("176.223.135.151", "176.223.135.151"));
		vSeeds.push_back(CDNSSeedData("62.77.157.99", "62.77.157.99"));
		vSeeds.push_back(CDNSSeedData("89.47.160.99", "89.47.160.99"));
		vSeeds.push_back(CDNSSeedData("45.77.119.123", "45.77.119.123"));
		vSeeds.push_back(CDNSSeedData("144.202.93.90", "144.202.93.90"));
		vSeeds.push_back(CDNSSeedData("80.209.238.12", "80.209.238.12"));
		vSeeds.push_back(CDNSSeedData("80.209.233.236", "80.209.233.236"));
		vSeeds.push_back(CDNSSeedData("62.77.154.196", "62.77.154.196"));
		vSeeds.push_back(CDNSSeedData("89.40.12.103", "89.40.12.103"));
		vSeeds.push_back(CDNSSeedData("81.24.214.150", "81.24.214.150"));
		vSeeds.push_back(CDNSSeedData("85.214.124.197", "85.214.124.197"));
		vSeeds.push_back(CDNSSeedData("108.61.196.116", "108.61.196.116"));
		vSeeds.push_back(CDNSSeedData("62.77.157.103", "62.77.157.103"));
		vSeeds.push_back(CDNSSeedData("209.250.255.45", "209.250.255.45"));
		vSeeds.push_back(CDNSSeedData("45.32.241.18", "45.32.241.18"));
		vSeeds.push_back(CDNSSeedData("39.104.115.23", "39.104.115.23"));
		vSeeds.push_back(CDNSSeedData("140.82.57.199", "140.82.57.199"));
		vSeeds.push_back(CDNSSeedData("45.77.248.15", "45.77.248.15"));
		vSeeds.push_back(CDNSSeedData("176.223.139.219", "176.223.139.219"));
		vSeeds.push_back(CDNSSeedData("62.77.155.210", "62.77.155.210"));
		vSeeds.push_back(CDNSSeedData("89.47.161.178", "89.47.161.178"));
		vSeeds.push_back(CDNSSeedData("89.47.160.89", "89.47.160.89"));
		vSeeds.push_back(CDNSSeedData("194.135.94.37", "194.135.94.37"));
		vSeeds.push_back(CDNSSeedData("202.182.98.119", "202.182.98.119"));
		vSeeds.push_back(CDNSSeedData("108.61.171.251", "108.61.171.251"));
		vSeeds.push_back(CDNSSeedData("45.77.67.12", "45.77.67.12"));
		vSeeds.push_back(CDNSSeedData("173.212.248.30", "173.212.248.30"));
		vSeeds.push_back(CDNSSeedData("176.223.129.197", "176.223.129.197"));
		vSeeds.push_back(CDNSSeedData("89.40.5.138", "89.40.5.138"));
		vSeeds.push_back(CDNSSeedData("176.223.128.223", "176.223.128.223"));
		vSeeds.push_back(CDNSSeedData("81.24.214.153", "81.24.214.153"));
		vSeeds.push_back(CDNSSeedData("45.32.166.252", "45.32.166.252"));
		vSeeds.push_back(CDNSSeedData("140.82.31.122", "140.82.31.122"));
		vSeeds.push_back(CDNSSeedData("103.72.164.156", "103.72.164.156"));
		vSeeds.push_back(CDNSSeedData("89.47.165.175", "89.47.165.175"));
		vSeeds.push_back(CDNSSeedData("149.28.156.207", "149.28.156.207"));
		vSeeds.push_back(CDNSSeedData("107.174.245.112", "107.174.245.112"));
		vSeeds.push_back(CDNSSeedData("47.89.21.62", "47.89.21.62"));
		vSeeds.push_back(CDNSSeedData("89.40.0.253", "89.40.0.253"));
		vSeeds.push_back(CDNSSeedData("89.47.165.159", "89.47.165.159"));
		vSeeds.push_back(CDNSSeedData("176.223.130.156", "176.223.130.156"));
		vSeeds.push_back(CDNSSeedData("108.61.187.15", "108.61.187.15"));
		vSeeds.push_back(CDNSSeedData("89.40.4.111", "89.40.4.111"));
		vSeeds.push_back(CDNSSeedData("45.63.3.216", "45.63.3.216"));
		vSeeds.push_back(CDNSSeedData("176.223.133.134", "176.223.133.134"));
		vSeeds.push_back(CDNSSeedData("45.77.110.221", "45.77.110.221"));
		vSeeds.push_back(CDNSSeedData("54.179.154.252", "54.179.154.252"));
		vSeeds.push_back(CDNSSeedData("89.40.7.13", "89.40.7.13"));
		vSeeds.push_back(CDNSSeedData("45.77.114.155", "45.77.114.155"));
		vSeeds.push_back(CDNSSeedData("89.40.13.140", "89.40.13.140"));
		vSeeds.push_back(CDNSSeedData("144.202.102.198", "144.202.102.198"));
		vSeeds.push_back(CDNSSeedData("45.63.122.63", "45.63.122.63"));
		vSeeds.push_back(CDNSSeedData("196.53.104.147", "196.53.104.147"));
		vSeeds.push_back(CDNSSeedData("107.175.38.211", "107.175.38.211"));
		vSeeds.push_back(CDNSSeedData("194.135.81.14", "194.135.81.14"));
		vSeeds.push_back(CDNSSeedData("207.148.106.214", "207.148.106.214"));
		vSeeds.push_back(CDNSSeedData("140.82.38.242", "140.82.38.242"));
		vSeeds.push_back(CDNSSeedData("176.223.131.121", "176.223.131.121"));
		vSeeds.push_back(CDNSSeedData("62.77.155.198", "62.77.155.198"));
		vSeeds.push_back(CDNSSeedData("109.235.65.156", "109.235.65.156"));
		vSeeds.push_back(CDNSSeedData("209.250.230.190", "209.250.230.190"));
		vSeeds.push_back(CDNSSeedData("149.28.22.228", "149.28.22.228"));
		vSeeds.push_back(CDNSSeedData("45.32.11.129", "45.32.11.129"));
		vSeeds.push_back(CDNSSeedData("62.77.153.159", "62.77.153.159"));
		vSeeds.push_back(CDNSSeedData("45.76.248.156", "45.76.248.156"));
		vSeeds.push_back(CDNSSeedData("185.206.145.61", "185.206.145.61"));
		vSeeds.push_back(CDNSSeedData("45.77.201.251", "45.77.201.251"));
		vSeeds.push_back(CDNSSeedData("176.223.131.147", "176.223.131.147"));
		vSeeds.push_back(CDNSSeedData("176.223.139.7", "176.223.139.7"));
		vSeeds.push_back(CDNSSeedData("89.47.160.77", "89.47.160.77"));
		vSeeds.push_back(CDNSSeedData("103.45.110.242", "103.45.110.242"));
		vSeeds.push_back(CDNSSeedData("199.247.6.153", "199.247.6.153"));
		vSeeds.push_back(CDNSSeedData("80.211.146.234", "80.211.146.234"));
		vSeeds.push_back(CDNSSeedData("194.135.89.8", "194.135.89.8"));
		vSeeds.push_back(CDNSSeedData("45.63.88.134", "45.63.88.134"));
		vSeeds.push_back(CDNSSeedData("95.179.146.126", "95.179.146.126"));
		vSeeds.push_back(CDNSSeedData("94.16.116.182", "94.16.116.182"));
		vSeeds.push_back(CDNSSeedData("194.135.84.119", "194.135.84.119"));
		vSeeds.push_back(CDNSSeedData("62.77.158.173", "62.77.158.173"));
		vSeeds.push_back(CDNSSeedData("45.76.227.113", "45.76.227.113"));
		vSeeds.push_back(CDNSSeedData("47.92.32.17", "47.92.32.17"));
		vSeeds.push_back(CDNSSeedData("89.40.5.116", "89.40.5.116"));
		vSeeds.push_back(CDNSSeedData("104.238.149.71", "104.238.149.71"));
		vSeeds.push_back(CDNSSeedData("47.254.151.39", "47.254.151.39"));
		vSeeds.push_back(CDNSSeedData("89.47.163.164", "89.47.163.164"));
		vSeeds.push_back(CDNSSeedData("45.63.68.28", "45.63.68.28"));
		vSeeds.push_back(CDNSSeedData("62.77.155.148", "62.77.155.148"));
		vSeeds.push_back(CDNSSeedData("159.65.236.212", "159.65.236.212"));
		vSeeds.push_back(CDNSSeedData("149.210.236.210", "149.210.236.210"));
		vSeeds.push_back(CDNSSeedData("185.233.105.237", "185.233.105.237"));
		vSeeds.push_back(CDNSSeedData("51.15.255.140", "51.15.255.140"));
		vSeeds.push_back(CDNSSeedData("144.202.86.142", "144.202.86.142"));
		vSeeds.push_back(CDNSSeedData("62.77.159.147", "62.77.159.147"));
		vSeeds.push_back(CDNSSeedData("94.176.239.240", "94.176.239.240"));
		vSeeds.push_back(CDNSSeedData("62.77.155.110", "62.77.155.110"));
		vSeeds.push_back(CDNSSeedData("89.47.166.159", "89.47.166.159"));
		vSeeds.push_back(CDNSSeedData("80.209.238.160", "80.209.238.160"));
		vSeeds.push_back(CDNSSeedData("195.181.247.31", "195.181.247.31"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("80.209.233.185", "80.209.233.185"));
		vSeeds.push_back(CDNSSeedData("38.103.14.20", "38.103.14.20"));
		vSeeds.push_back(CDNSSeedData("176.223.138.163", "176.223.138.163"));
		vSeeds.push_back(CDNSSeedData("89.22.101.214", "89.22.101.214"));
		vSeeds.push_back(CDNSSeedData("89.47.160.80", "89.47.160.80"));
		vSeeds.push_back(CDNSSeedData("207.148.75.232", "207.148.75.232"));
		vSeeds.push_back(CDNSSeedData("206.217.143.83", "206.217.143.83"));
		vSeeds.push_back(CDNSSeedData("80.209.233.214", "80.209.233.214"));
		vSeeds.push_back(CDNSSeedData("108.61.171.120", "108.61.171.120"));
		vSeeds.push_back(CDNSSeedData("94.16.119.49", "94.16.119.49"));
		vSeeds.push_back(CDNSSeedData("176.223.130.211", "176.223.130.211"));
		vSeeds.push_back(CDNSSeedData("176.223.133.16", "176.223.133.16"));
		vSeeds.push_back(CDNSSeedData("176.223.129.188", "176.223.129.188"));
		vSeeds.push_back(CDNSSeedData("176.223.132.130", "176.223.132.130"));
		vSeeds.push_back(CDNSSeedData("80.209.225.18", "80.209.225.18"));
		vSeeds.push_back(CDNSSeedData("212.237.52.81", "212.237.52.81"));
		vSeeds.push_back(CDNSSeedData("45.32.150.6", "45.32.150.6"));
		vSeeds.push_back(CDNSSeedData("45.32.135.48", "45.32.135.48"));
		vSeeds.push_back(CDNSSeedData("5.45.111.106", "5.45.111.106"));
		vSeeds.push_back(CDNSSeedData("23.95.90.77", "23.95.90.77"));
		vSeeds.push_back(CDNSSeedData("45.76.136.167", "45.76.136.167"));
		vSeeds.push_back(CDNSSeedData("47.92.64.225", "47.92.64.225"));
		vSeeds.push_back(CDNSSeedData("176.223.131.126", "176.223.131.126"));
		vSeeds.push_back(CDNSSeedData("144.202.45.249", "144.202.45.249"));
		vSeeds.push_back(CDNSSeedData("149.28.39.5", "149.28.39.5"));
		vSeeds.push_back(CDNSSeedData("89.40.13.112", "89.40.13.112"));
		vSeeds.push_back(CDNSSeedData("89.47.160.178", "89.47.160.178"));
		vSeeds.push_back(CDNSSeedData("23.94.137.127", "23.94.137.127"));
		vSeeds.push_back(CDNSSeedData("51.15.46.223", "51.15.46.223"));
		vSeeds.push_back(CDNSSeedData("185.219.81.35", "185.219.81.35"));
		vSeeds.push_back(CDNSSeedData("47.92.134.145", "47.92.134.145"));
		vSeeds.push_back(CDNSSeedData("31.214.144.251", "31.214.144.251"));
		vSeeds.push_back(CDNSSeedData("80.209.225.52", "80.209.225.52"));
		vSeeds.push_back(CDNSSeedData("94.176.236.225", "94.176.236.225"));
		vSeeds.push_back(CDNSSeedData("62.77.157.206", "62.77.157.206"));
		vSeeds.push_back(CDNSSeedData("89.163.144.233", "89.163.144.233"));
		vSeeds.push_back(CDNSSeedData("207.148.64.111", "207.148.64.111"));
		vSeeds.push_back(CDNSSeedData("80.209.226.167", "80.209.226.167"));
		vSeeds.push_back(CDNSSeedData("209.250.255.99", "209.250.255.99"));
		vSeeds.push_back(CDNSSeedData("138.201.152.44", "138.201.152.44"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("159.203.93.39", "159.203.93.39"));
		vSeeds.push_back(CDNSSeedData("89.47.165.253", "89.47.165.253"));
		vSeeds.push_back(CDNSSeedData("51.15.199.129", "51.15.199.129"));
		vSeeds.push_back(CDNSSeedData("194.135.82.82", "194.135.82.82"));
		vSeeds.push_back(CDNSSeedData("89.40.2.57", "89.40.2.57"));
		vSeeds.push_back(CDNSSeedData("199.247.9.18", "199.247.9.18"));
		vSeeds.push_back(CDNSSeedData("51.15.212.119", "51.15.212.119"));
		vSeeds.push_back(CDNSSeedData("94.176.234.157", "94.176.234.157"));
		vSeeds.push_back(CDNSSeedData("86.121.208.47", "86.121.208.47"));
		vSeeds.push_back(CDNSSeedData("176.223.134.246", "176.223.134.246"));
		vSeeds.push_back(CDNSSeedData("144.202.97.36", "144.202.97.36"));
		vSeeds.push_back(CDNSSeedData("45.77.129.136", "45.77.129.136"));
		vSeeds.push_back(CDNSSeedData("80.208.230.218", "80.208.230.218"));
		vSeeds.push_back(CDNSSeedData("50.3.82.192", "50.3.82.192"));
		vSeeds.push_back(CDNSSeedData("104.237.147.43", "104.237.147.43"));
		vSeeds.push_back(CDNSSeedData("145.239.83.81", "145.239.83.81"));
		vSeeds.push_back(CDNSSeedData("52.91.63.63", "52.91.63.63"));
		vSeeds.push_back(CDNSSeedData("163.172.190.31", "163.172.190.31"));
		vSeeds.push_back(CDNSSeedData("89.40.15.75", "89.40.15.75"));
		vSeeds.push_back(CDNSSeedData("45.32.222.15", "45.32.222.15"));
		vSeeds.push_back(CDNSSeedData("45.76.1.66", "45.76.1.66"));
		vSeeds.push_back(CDNSSeedData("45.76.4.105", "45.76.4.105"));
		vSeeds.push_back(CDNSSeedData("89.47.164.87", "89.47.164.87"));
		vSeeds.push_back(CDNSSeedData("95.179.147.215", "95.179.147.215"));
		vSeeds.push_back(CDNSSeedData("174.138.4.156", "174.138.4.156"));
		vSeeds.push_back(CDNSSeedData("80.209.238.227", "80.209.238.227"));
		vSeeds.push_back(CDNSSeedData("199.247.22.153", "199.247.22.153"));
		vSeeds.push_back(CDNSSeedData("144.202.73.26", "144.202.73.26"));
		vSeeds.push_back(CDNSSeedData("80.209.225.2", "80.209.225.2"));
		vSeeds.push_back(CDNSSeedData("62.77.157.54", "62.77.157.54"));
		vSeeds.push_back(CDNSSeedData("80.208.226.237", "80.208.226.237"));
		vSeeds.push_back(CDNSSeedData("89.40.7.217", "89.40.7.217"));
		vSeeds.push_back(CDNSSeedData("89.40.6.37", "89.40.6.37"));
		vSeeds.push_back(CDNSSeedData("149.56.246.74", "149.56.246.74"));
		vSeeds.push_back(CDNSSeedData("45.32.211.4", "45.32.211.4"));
		vSeeds.push_back(CDNSSeedData("176.223.143.54", "176.223.143.54"));
		vSeeds.push_back(CDNSSeedData("199.247.1.107", "199.247.1.107"));
		vSeeds.push_back(CDNSSeedData("89.47.160.109", "89.47.160.109"));
		vSeeds.push_back(CDNSSeedData("89.47.160.81", "89.47.160.81"));
		vSeeds.push_back(CDNSSeedData("176.223.130.159", "176.223.130.159"));
		vSeeds.push_back(CDNSSeedData("80.209.235.164", "80.209.235.164"));
		vSeeds.push_back(CDNSSeedData("144.202.11.82", "144.202.11.82"));
		vSeeds.push_back(CDNSSeedData("45.32.141.26", "45.32.141.26"));
		vSeeds.push_back(CDNSSeedData("188.166.64.138", "188.166.64.138"));
		vSeeds.push_back(CDNSSeedData("45.32.133.43", "45.32.133.43"));
		vSeeds.push_back(CDNSSeedData("159.65.72.113", "159.65.72.113"));
		vSeeds.push_back(CDNSSeedData("149.28.37.20", "149.28.37.20"));
		vSeeds.push_back(CDNSSeedData("104.207.139.164", "104.207.139.164"));
		vSeeds.push_back(CDNSSeedData("140.82.37.159", "140.82.37.159"));
		vSeeds.push_back(CDNSSeedData("185.58.207.41", "185.58.207.41"));
		vSeeds.push_back(CDNSSeedData("45.77.8.137", "45.77.8.137"));
		vSeeds.push_back(CDNSSeedData("89.47.164.2", "89.47.164.2"));
		vSeeds.push_back(CDNSSeedData("45.77.61.137", "45.77.61.137"));
		vSeeds.push_back(CDNSSeedData("212.24.100.235", "212.24.100.235"));
		vSeeds.push_back(CDNSSeedData("62.77.159.151", "62.77.159.151"));
		vSeeds.push_back(CDNSSeedData("194.135.83.84", "194.135.83.84"));
		vSeeds.push_back(CDNSSeedData("89.40.13.167", "89.40.13.167"));
		vSeeds.push_back(CDNSSeedData("206.189.196.14", "206.189.196.14"));
		vSeeds.push_back(CDNSSeedData("47.92.39.213", "47.92.39.213"));
		vSeeds.push_back(CDNSSeedData("209.250.247.210", "209.250.247.210"));
		vSeeds.push_back(CDNSSeedData("52.55.72.181", "52.55.72.181"));
		vSeeds.push_back(CDNSSeedData("89.40.5.48", "89.40.5.48"));
		vSeeds.push_back(CDNSSeedData("207.148.81.202", "207.148.81.202"));
		vSeeds.push_back(CDNSSeedData("47.95.241.1", "47.95.241.1"));
		vSeeds.push_back(CDNSSeedData("149.28.119.207", "149.28.119.207"));
		vSeeds.push_back(CDNSSeedData("108.61.210.198", "108.61.210.198"));
		vSeeds.push_back(CDNSSeedData("62.77.159.240", "62.77.159.240"));
		vSeeds.push_back(CDNSSeedData("176.223.128.75", "176.223.128.75"));
		vSeeds.push_back(CDNSSeedData("159.89.180.89", "159.89.180.89"));
		vSeeds.push_back(CDNSSeedData("176.223.134.248", "176.223.134.248"));
		vSeeds.push_back(CDNSSeedData("45.32.19.217", "45.32.19.217"));
		vSeeds.push_back(CDNSSeedData("206.189.0.15", "206.189.0.15"));
		vSeeds.push_back(CDNSSeedData("144.202.22.157", "144.202.22.157"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("209.97.163.95", "209.97.163.95"));
		vSeeds.push_back(CDNSSeedData("149.28.25.181", "149.28.25.181"));
		vSeeds.push_back(CDNSSeedData("89.47.165.161", "89.47.165.161"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("104.168.126.177", "104.168.126.177"));
		vSeeds.push_back(CDNSSeedData("104.156.232.65", "104.156.232.65"));
		vSeeds.push_back(CDNSSeedData("104.238.146.27", "104.238.146.27"));
		vSeeds.push_back(CDNSSeedData("89.40.6.137", "89.40.6.137"));
		vSeeds.push_back(CDNSSeedData("89.47.164.86", "89.47.164.86"));
		vSeeds.push_back(CDNSSeedData("199.247.29.243", "199.247.29.243"));
		vSeeds.push_back(CDNSSeedData("89.47.167.161", "89.47.167.161"));
		vSeeds.push_back(CDNSSeedData("89.47.160.85", "89.47.160.85"));
		vSeeds.push_back(CDNSSeedData("62.77.159.140", "62.77.159.140"));
		vSeeds.push_back(CDNSSeedData("62.77.159.61", "62.77.159.61"));
		vSeeds.push_back(CDNSSeedData("80.209.231.52", "80.209.231.52"));
		vSeeds.push_back(CDNSSeedData("80.209.235.111", "80.209.235.111"));
		vSeeds.push_back(CDNSSeedData("18.216.29.55", "18.216.29.55"));
		vSeeds.push_back(CDNSSeedData("149.28.49.134", "149.28.49.134"));
		vSeeds.push_back(CDNSSeedData("89.47.165.252", "89.47.165.252"));
		vSeeds.push_back(CDNSSeedData("80.208.231.34", "80.208.231.34"));
		vSeeds.push_back(CDNSSeedData("89.40.6.100", "89.40.6.100"));
		vSeeds.push_back(CDNSSeedData("195.181.244.143", "195.181.244.143"));
		vSeeds.push_back(CDNSSeedData("104.238.145.220", "104.238.145.220"));
		vSeeds.push_back(CDNSSeedData("158.69.214.87", "158.69.214.87"));
		vSeeds.push_back(CDNSSeedData("212.47.240.5", "212.47.240.5"));
		vSeeds.push_back(CDNSSeedData("144.202.74.73", "144.202.74.73"));
		vSeeds.push_back(CDNSSeedData("149.28.123.2", "149.28.123.2"));
		vSeeds.push_back(CDNSSeedData("199.247.21.55", "199.247.21.55"));
		vSeeds.push_back(CDNSSeedData("104.238.159.220", "104.238.159.220"));
		vSeeds.push_back(CDNSSeedData("89.40.2.228", "89.40.2.228"));
		vSeeds.push_back(CDNSSeedData("140.82.34.161", "140.82.34.161"));
		vSeeds.push_back(CDNSSeedData("80.209.237.235", "80.209.237.235"));
		vSeeds.push_back(CDNSSeedData("45.63.91.140", "45.63.91.140"));
		vSeeds.push_back(CDNSSeedData("209.250.227.88", "209.250.227.88"));
		vSeeds.push_back(CDNSSeedData("207.148.91.224", "207.148.91.224"));
		vSeeds.push_back(CDNSSeedData("80.211.85.97", "80.211.85.97"));
		vSeeds.push_back(CDNSSeedData("206.189.21.105", "206.189.21.105"));
		vSeeds.push_back(CDNSSeedData("144.202.15.94", "144.202.15.94"));
		vSeeds.push_back(CDNSSeedData("149.28.234.189", "149.28.234.189"));
		vSeeds.push_back(CDNSSeedData("185.137.219.135", "185.137.219.135"));
		vSeeds.push_back(CDNSSeedData("176.223.129.201", "176.223.129.201"));
		vSeeds.push_back(CDNSSeedData("144.202.71.221", "144.202.71.221"));
		vSeeds.push_back(CDNSSeedData("202.182.108.253", "202.182.108.253"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("39.107.69.62", "39.107.69.62"));
		vSeeds.push_back(CDNSSeedData("173.199.70.151", "173.199.70.151"));
		vSeeds.push_back(CDNSSeedData("45.32.172.236", "45.32.172.236"));
		vSeeds.push_back(CDNSSeedData("45.32.229.32", "45.32.229.32"));
		vSeeds.push_back(CDNSSeedData("47.92.1.175", "47.92.1.175"));
		vSeeds.push_back(CDNSSeedData("138.197.173.120", "138.197.173.120"));
		vSeeds.push_back(CDNSSeedData("47.92.71.101", "47.92.71.101"));
		vSeeds.push_back(CDNSSeedData("192.241.193.55", "192.241.193.55"));
		vSeeds.push_back(CDNSSeedData("149.28.245.164", "149.28.245.164"));
		vSeeds.push_back(CDNSSeedData("89.40.10.125", "89.40.10.125"));
		vSeeds.push_back(CDNSSeedData("149.28.166.225", "149.28.166.225"));
		vSeeds.push_back(CDNSSeedData("123.234.118.13", "123.234.118.13"));
		vSeeds.push_back(CDNSSeedData("185.92.220.133", "185.92.220.133"));
		vSeeds.push_back(CDNSSeedData("51.15.151.178", "51.15.151.178"));
		vSeeds.push_back(CDNSSeedData("104.207.151.84", "104.207.151.84"));
		vSeeds.push_back(CDNSSeedData("176.223.129.124", "176.223.129.124"));
		vSeeds.push_back(CDNSSeedData("199.247.19.171", "199.247.19.171"));
		vSeeds.push_back(CDNSSeedData("176.223.137.140", "176.223.137.140"));
		vSeeds.push_back(CDNSSeedData("104.207.129.193", "104.207.129.193"));
		vSeeds.push_back(CDNSSeedData("45.77.246.216", "45.77.246.216"));
		vSeeds.push_back(CDNSSeedData("89.47.161.145", "89.47.161.145"));
		vSeeds.push_back(CDNSSeedData("185.174.173.56", "185.174.173.56"));
		vSeeds.push_back(CDNSSeedData("144.202.72.246", "144.202.72.246"));
		vSeeds.push_back(CDNSSeedData("198.199.104.157", "198.199.104.157"));
		vSeeds.push_back(CDNSSeedData("45.56.109.209", "45.56.109.209"));
		vSeeds.push_back(CDNSSeedData("80.209.235.2", "80.209.235.2"));
		vSeeds.push_back(CDNSSeedData("107.173.222.132", "107.173.222.132"));
		vSeeds.push_back(CDNSSeedData("72.14.179.5", "72.14.179.5"));
		vSeeds.push_back(CDNSSeedData("89.40.13.70", "89.40.13.70"));
		vSeeds.push_back(CDNSSeedData("176.223.132.64", "176.223.132.64"));
		vSeeds.push_back(CDNSSeedData("45.77.143.215", "45.77.143.215"));
		vSeeds.push_back(CDNSSeedData("51.15.222.162", "51.15.222.162"));
		vSeeds.push_back(CDNSSeedData("138.201.152.149", "138.201.152.149"));
		vSeeds.push_back(CDNSSeedData("45.76.230.121", "45.76.230.121"));
		vSeeds.push_back(CDNSSeedData("80.209.231.29", "80.209.231.29"));
		vSeeds.push_back(CDNSSeedData("62.77.157.187", "62.77.157.187"));
		vSeeds.push_back(CDNSSeedData("45.76.38.180", "45.76.38.180"));
		vSeeds.push_back(CDNSSeedData("80.208.228.29", "80.208.228.29"));
		vSeeds.push_back(CDNSSeedData("45.76.161.176", "45.76.161.176"));
		vSeeds.push_back(CDNSSeedData("78.200.9.26", "78.200.9.26"));
		vSeeds.push_back(CDNSSeedData("120.79.173.60", "120.79.173.60"));
		vSeeds.push_back(CDNSSeedData("80.208.231.224", "80.208.231.224"));
		vSeeds.push_back(CDNSSeedData("199.247.20.183", "199.247.20.183"));
		vSeeds.push_back(CDNSSeedData("89.40.10.111", "89.40.10.111"));
		vSeeds.push_back(CDNSSeedData("208.167.239.165", "208.167.239.165"));
		vSeeds.push_back(CDNSSeedData("45.32.200.72", "45.32.200.72"));
		vSeeds.push_back(CDNSSeedData("63.209.32.96", "63.209.32.96"));
		vSeeds.push_back(CDNSSeedData("167.99.170.123", "167.99.170.123"));
		vSeeds.push_back(CDNSSeedData("5.135.75.35", "5.135.75.35"));
		vSeeds.push_back(CDNSSeedData("89.40.11.146", "89.40.11.146"));
		vSeeds.push_back(CDNSSeedData("62.77.156.215", "62.77.156.215"));
		vSeeds.push_back(CDNSSeedData("38.127.169.150", "38.127.169.150"));
		vSeeds.push_back(CDNSSeedData("89.47.164.88", "89.47.164.88"));
		vSeeds.push_back(CDNSSeedData("45.77.90.236", "45.77.90.236"));
		vSeeds.push_back(CDNSSeedData("108.61.195.34", "108.61.195.34"));
		vSeeds.push_back(CDNSSeedData("89.40.6.36", "89.40.6.36"));
		vSeeds.push_back(CDNSSeedData("107.191.47.197", "107.191.47.197"));
		vSeeds.push_back(CDNSSeedData("94.176.235.8", "94.176.235.8"));
		vSeeds.push_back(CDNSSeedData("80.208.225.216", "80.208.225.216"));
		vSeeds.push_back(CDNSSeedData("149.28.35.12", "149.28.35.12"));
		vSeeds.push_back(CDNSSeedData("149.210.197.106", "149.210.197.106"));
		vSeeds.push_back(CDNSSeedData("89.47.160.63", "89.47.160.63"));
		vSeeds.push_back(CDNSSeedData("140.82.62.60", "140.82.62.60"));
		vSeeds.push_back(CDNSSeedData("172.104.245.54", "172.104.245.54"));
		vSeeds.push_back(CDNSSeedData("212.237.10.36", "212.237.10.36"));
		vSeeds.push_back(CDNSSeedData("47.92.119.174", "47.92.119.174"));
		vSeeds.push_back(CDNSSeedData("198.13.34.110", "198.13.34.110"));
		vSeeds.push_back(CDNSSeedData("176.223.138.162", "176.223.138.162"));
		vSeeds.push_back(CDNSSeedData("89.47.166.240", "89.47.166.240"));
		vSeeds.push_back(CDNSSeedData("62.77.153.96", "62.77.153.96"));
		vSeeds.push_back(CDNSSeedData("45.76.61.86", "45.76.61.86"));
		vSeeds.push_back(CDNSSeedData("47.92.29.203", "47.92.29.203"));
		vSeeds.push_back(CDNSSeedData("54.219.131.208", "54.219.131.208"));
		vSeeds.push_back(CDNSSeedData("89.40.10.64", "89.40.10.64"));
		vSeeds.push_back(CDNSSeedData("173.199.90.205", "173.199.90.205"));
		vSeeds.push_back(CDNSSeedData("176.223.139.213", "176.223.139.213"));
		vSeeds.push_back(CDNSSeedData("149.28.170.195", "149.28.170.195"));
		vSeeds.push_back(CDNSSeedData("209.250.229.49", "209.250.229.49"));
		vSeeds.push_back(CDNSSeedData("62.77.158.105", "62.77.158.105"));
		vSeeds.push_back(CDNSSeedData("104.238.141.77", "104.238.141.77"));
		vSeeds.push_back(CDNSSeedData("63.209.32.111", "63.209.32.111"));
		vSeeds.push_back(CDNSSeedData("62.77.156.224", "62.77.156.224"));
		vSeeds.push_back(CDNSSeedData("89.40.10.116", "89.40.10.116"));
		vSeeds.push_back(CDNSSeedData("62.77.156.209", "62.77.156.209"));
		vSeeds.push_back(CDNSSeedData("89.47.166.243", "89.47.166.243"));
		vSeeds.push_back(CDNSSeedData("176.223.131.248", "176.223.131.248"));
		vSeeds.push_back(CDNSSeedData("62.77.154.97", "62.77.154.97"));
		vSeeds.push_back(CDNSSeedData("217.61.105.248", "217.61.105.248"));
		vSeeds.push_back(CDNSSeedData("149.28.198.68", "149.28.198.68"));
		vSeeds.push_back(CDNSSeedData("176.223.143.178", "176.223.143.178"));
		vSeeds.push_back(CDNSSeedData("89.40.12.56", "89.40.12.56"));
		vSeeds.push_back(CDNSSeedData("54.39.96.188", "54.39.96.188"));
		vSeeds.push_back(CDNSSeedData("222.154.43.212", "222.154.43.212"));
		vSeeds.push_back(CDNSSeedData("89.40.14.15", "89.40.14.15"));
		vSeeds.push_back(CDNSSeedData("103.57.209.84", "103.57.209.84"));
		vSeeds.push_back(CDNSSeedData("95.179.136.22", "95.179.136.22"));
		vSeeds.push_back(CDNSSeedData("176.223.128.136", "176.223.128.136"));
		vSeeds.push_back(CDNSSeedData("80.209.231.50", "80.209.231.50"));
		vSeeds.push_back(CDNSSeedData("95.179.158.53", "95.179.158.53"));
		vSeeds.push_back(CDNSSeedData("176.223.138.169", "176.223.138.169"));
		vSeeds.push_back(CDNSSeedData("45.77.250.126", "45.77.250.126"));
		vSeeds.push_back(CDNSSeedData("45.76.184.222", "45.76.184.222"));
		vSeeds.push_back(CDNSSeedData("45.32.87.182", "45.32.87.182"));
		vSeeds.push_back(CDNSSeedData("108.61.96.43", "108.61.96.43"));
		vSeeds.push_back(CDNSSeedData("207.246.79.142", "207.246.79.142"));
		vSeeds.push_back(CDNSSeedData("178.32.113.197", "178.32.113.197"));
		vSeeds.push_back(CDNSSeedData("37.120.173.147", "37.120.173.147"));
		vSeeds.push_back(CDNSSeedData("69.165.192.43", "69.165.192.43"));
		vSeeds.push_back(CDNSSeedData("50.116.44.148", "50.116.44.148"));
		vSeeds.push_back(CDNSSeedData("39.106.156.82", "39.106.156.82"));
		vSeeds.push_back(CDNSSeedData("80.209.234.58", "80.209.234.58"));
		vSeeds.push_back(CDNSSeedData("62.77.159.145", "62.77.159.145"));
		vSeeds.push_back(CDNSSeedData("89.40.5.117", "89.40.5.117"));
		vSeeds.push_back(CDNSSeedData("68.232.175.216", "68.232.175.216"));
		vSeeds.push_back(CDNSSeedData("45.76.255.7", "45.76.255.7"));
		vSeeds.push_back(CDNSSeedData("80.208.229.170", "80.208.229.170"));
		vSeeds.push_back(CDNSSeedData("95.216.136.200", "95.216.136.200"));
		vSeeds.push_back(CDNSSeedData("45.77.228.228", "45.77.228.228"));
		vSeeds.push_back(CDNSSeedData("45.76.95.181", "45.76.95.181"));
		vSeeds.push_back(CDNSSeedData("108.61.171.185", "108.61.171.185"));
		vSeeds.push_back(CDNSSeedData("176.223.141.253", "176.223.141.253"));
		vSeeds.push_back(CDNSSeedData("89.47.160.6", "89.47.160.6"));
		vSeeds.push_back(CDNSSeedData("176.223.128.224", "176.223.128.224"));
		vSeeds.push_back(CDNSSeedData("38.127.169.145", "38.127.169.145"));
		vSeeds.push_back(CDNSSeedData("80.209.226.55", "80.209.226.55"));
		vSeeds.push_back(CDNSSeedData("207.148.25.238", "207.148.25.238"));
		vSeeds.push_back(CDNSSeedData("209.250.236.119", "209.250.236.119"));
		vSeeds.push_back(CDNSSeedData("95.179.135.69", "95.179.135.69"));
		vSeeds.push_back(CDNSSeedData("46.101.136.35", "46.101.136.35"));
		vSeeds.push_back(CDNSSeedData("81.2.255.158", "81.2.255.158"));
		vSeeds.push_back(CDNSSeedData("82.223.65.94", "82.223.65.94"));
		vSeeds.push_back(CDNSSeedData("62.77.152.129", "62.77.152.129"));
		vSeeds.push_back(CDNSSeedData("176.223.137.94", "176.223.137.94"));
		vSeeds.push_back(CDNSSeedData("89.40.11.68", "89.40.11.68"));
		vSeeds.push_back(CDNSSeedData("89.40.6.97", "89.40.6.97"));
		vSeeds.push_back(CDNSSeedData("62.77.152.148", "62.77.152.148"));
		vSeeds.push_back(CDNSSeedData("109.73.4.244", "109.73.4.244"));
		vSeeds.push_back(CDNSSeedData("89.40.11.142", "89.40.11.142"));
		vSeeds.push_back(CDNSSeedData("94.176.234.184", "94.176.234.184"));
		vSeeds.push_back(CDNSSeedData("80.209.230.74", "80.209.230.74"));
		vSeeds.push_back(CDNSSeedData("209.250.228.207", "209.250.228.207"));
		vSeeds.push_back(CDNSSeedData("47.92.29.9", "47.92.29.9"));
		vSeeds.push_back(CDNSSeedData("89.47.165.158", "89.47.165.158"));
		vSeeds.push_back(CDNSSeedData("45.32.149.66", "45.32.149.66"));
		vSeeds.push_back(CDNSSeedData("89.47.160.73", "89.47.160.73"));
		vSeeds.push_back(CDNSSeedData("80.209.230.80", "80.209.230.80"));
		vSeeds.push_back(CDNSSeedData("149.28.137.171", "149.28.137.171"));
		vSeeds.push_back(CDNSSeedData("59.42.89.34", "59.42.89.34"));
		vSeeds.push_back(CDNSSeedData("176.9.28.175", "176.9.28.175"));
		vSeeds.push_back(CDNSSeedData("209.250.232.201", "209.250.232.201"));
		vSeeds.push_back(CDNSSeedData("89.40.4.119", "89.40.4.119"));
		vSeeds.push_back(CDNSSeedData("89.40.6.41", "89.40.6.41"));
		vSeeds.push_back(CDNSSeedData("176.223.137.19", "176.223.137.19"));
		vSeeds.push_back(CDNSSeedData("80.208.228.162", "80.208.228.162"));
		vSeeds.push_back(CDNSSeedData("47.92.69.37", "47.92.69.37"));
		vSeeds.push_back(CDNSSeedData("194.135.80.122", "194.135.80.122"));
		vSeeds.push_back(CDNSSeedData("207.148.79.162", "207.148.79.162"));
		vSeeds.push_back(CDNSSeedData("45.32.201.219", "45.32.201.219"));
		vSeeds.push_back(CDNSSeedData("89.40.11.196", "89.40.11.196"));
		vSeeds.push_back(CDNSSeedData("149.28.246.77", "149.28.246.77"));
		vSeeds.push_back(CDNSSeedData("45.63.40.73", "45.63.40.73"));
		vSeeds.push_back(CDNSSeedData("47.92.83.66", "47.92.83.66"));
		vSeeds.push_back(CDNSSeedData("144.202.76.60", "144.202.76.60"));
		vSeeds.push_back(CDNSSeedData("149.28.59.234", "149.28.59.234"));
		vSeeds.push_back(CDNSSeedData("206.189.57.153", "206.189.57.153"));
		vSeeds.push_back(CDNSSeedData("199.247.7.137", "199.247.7.137"));
		vSeeds.push_back(CDNSSeedData("80.209.233.68", "80.209.233.68"));
		vSeeds.push_back(CDNSSeedData("47.92.34.38", "47.92.34.38"));
		vSeeds.push_back(CDNSSeedData("45.77.235.149", "45.77.235.149"));
		vSeeds.push_back(CDNSSeedData("94.16.116.246", "94.16.116.246"));
		vSeeds.push_back(CDNSSeedData("188.138.68.198", "188.138.68.198"));
		vSeeds.push_back(CDNSSeedData("45.76.241.168", "45.76.241.168"));
		vSeeds.push_back(CDNSSeedData("47.92.133.103", "47.92.133.103"));
		vSeeds.push_back(CDNSSeedData("47.92.24.122", "47.92.24.122"));
		vSeeds.push_back(CDNSSeedData("198.13.41.92", "198.13.41.92"));
		vSeeds.push_back(CDNSSeedData("45.63.115.63", "45.63.115.63"));
		vSeeds.push_back(CDNSSeedData("89.40.14.11", "89.40.14.11"));
		vSeeds.push_back(CDNSSeedData("80.240.30.7", "80.240.30.7"));
		vSeeds.push_back(CDNSSeedData("185.15.244.239", "185.15.244.239"));
		vSeeds.push_back(CDNSSeedData("176.223.134.253", "176.223.134.253"));
		vSeeds.push_back(CDNSSeedData("89.40.2.231", "89.40.2.231"));
		vSeeds.push_back(CDNSSeedData("45.77.186.94", "45.77.186.94"));
		vSeeds.push_back(CDNSSeedData("47.75.15.60", "47.75.15.60"));
		vSeeds.push_back(CDNSSeedData("45.63.21.142", "45.63.21.142"));
		vSeeds.push_back(CDNSSeedData("89.40.5.114", "89.40.5.114"));
		vSeeds.push_back(CDNSSeedData("217.61.104.218", "217.61.104.218"));
		vSeeds.push_back(CDNSSeedData("80.208.231.202", "80.208.231.202"));
		vSeeds.push_back(CDNSSeedData("80.209.228.108", "80.209.228.108"));
		vSeeds.push_back(CDNSSeedData("89.47.160.245", "89.47.160.245"));
		vSeeds.push_back(CDNSSeedData("209.250.254.254", "209.250.254.254"));
		vSeeds.push_back(CDNSSeedData("80.79.194.67", "80.79.194.67"));
		vSeeds.push_back(CDNSSeedData("95.216.142.49", "95.216.142.49"));
		vSeeds.push_back(CDNSSeedData("217.163.28.54", "217.163.28.54"));
		vSeeds.push_back(CDNSSeedData("95.216.142.28", "95.216.142.28"));
		vSeeds.push_back(CDNSSeedData("159.203.74.241", "159.203.74.241"));
		vSeeds.push_back(CDNSSeedData("209.250.254.63", "209.250.254.63"));
		vSeeds.push_back(CDNSSeedData("45.76.26.183", "45.76.26.183"));
		vSeeds.push_back(CDNSSeedData("212.24.97.144", "212.24.97.144"));
		vSeeds.push_back(CDNSSeedData("89.40.0.218", "89.40.0.218"));
		vSeeds.push_back(CDNSSeedData("80.208.231.37", "80.208.231.37"));
		vSeeds.push_back(CDNSSeedData("176.223.128.70", "176.223.128.70"));
		vSeeds.push_back(CDNSSeedData("45.77.44.168", "45.77.44.168"));
		vSeeds.push_back(CDNSSeedData("23.95.242.7", "23.95.242.7"));
		vSeeds.push_back(CDNSSeedData("62.77.154.207", "62.77.154.207"));
		vSeeds.push_back(CDNSSeedData("89.40.1.198", "89.40.1.198"));
		vSeeds.push_back(CDNSSeedData("149.28.203.229", "149.28.203.229"));
		vSeeds.push_back(CDNSSeedData("62.77.155.47", "62.77.155.47"));
		vSeeds.push_back(CDNSSeedData("89.40.2.61", "89.40.2.61"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("149.28.170.115", "149.28.170.115"));
		vSeeds.push_back(CDNSSeedData("104.238.157.100", "104.238.157.100"));
		vSeeds.push_back(CDNSSeedData("89.40.4.235", "89.40.4.235"));
		vSeeds.push_back(CDNSSeedData("45.63.18.221", "45.63.18.221"));
		vSeeds.push_back(CDNSSeedData("45.77.53.3", "45.77.53.3"));
		vSeeds.push_back(CDNSSeedData("94.176.239.139", "94.176.239.139"));
		vSeeds.push_back(CDNSSeedData("45.63.99.170", "45.63.99.170"));
		vSeeds.push_back(CDNSSeedData("89.40.2.56", "89.40.2.56"));
		vSeeds.push_back(CDNSSeedData("172.245.241.141", "172.245.241.141"));
		vSeeds.push_back(CDNSSeedData("62.77.159.66", "62.77.159.66"));
		vSeeds.push_back(CDNSSeedData("89.40.10.123", "89.40.10.123"));
		vSeeds.push_back(CDNSSeedData("178.254.34.148", "178.254.34.148"));
		vSeeds.push_back(CDNSSeedData("176.223.129.128", "176.223.129.128"));
		vSeeds.push_back(CDNSSeedData("45.32.152.235", "45.32.152.235"));
		vSeeds.push_back(CDNSSeedData("80.208.228.195", "80.208.228.195"));
		vSeeds.push_back(CDNSSeedData("45.63.38.28", "45.63.38.28"));
		vSeeds.push_back(CDNSSeedData("89.47.164.81", "89.47.164.81"));
		vSeeds.push_back(CDNSSeedData("80.208.231.30", "80.208.231.30"));
		vSeeds.push_back(CDNSSeedData("80.208.225.172", "80.208.225.172"));
		vSeeds.push_back(CDNSSeedData("85.255.14.42", "85.255.14.42"));
		vSeeds.push_back(CDNSSeedData("47.92.73.47", "47.92.73.47"));
		vSeeds.push_back(CDNSSeedData("51.38.113.216", "51.38.113.216"));
		vSeeds.push_back(CDNSSeedData("89.40.12.158", "89.40.12.158"));
		vSeeds.push_back(CDNSSeedData("95.179.140.79", "95.179.140.79"));
		vSeeds.push_back(CDNSSeedData("89.47.162.190", "89.47.162.190"));
		vSeeds.push_back(CDNSSeedData("120.79.190.251", "120.79.190.251"));
		vSeeds.push_back(CDNSSeedData("185.80.222.206", "185.80.222.206"));
		vSeeds.push_back(CDNSSeedData("45.32.152.47", "45.32.152.47"));
		vSeeds.push_back(CDNSSeedData("185.233.105.151", "185.233.105.151"));
		vSeeds.push_back(CDNSSeedData("194.135.85.5", "194.135.85.5"));
		vSeeds.push_back(CDNSSeedData("176.223.143.133", "176.223.143.133"));
		vSeeds.push_back(CDNSSeedData("149.28.61.90", "149.28.61.90"));
		vSeeds.push_back(CDNSSeedData("80.209.229.6", "80.209.229.6"));
		vSeeds.push_back(CDNSSeedData("176.223.138.165", "176.223.138.165"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("144.202.45.199", "144.202.45.199"));
		vSeeds.push_back(CDNSSeedData("207.148.5.101", "207.148.5.101"));
		vSeeds.push_back(CDNSSeedData("208.167.233.109", "208.167.233.109"));
		vSeeds.push_back(CDNSSeedData("144.202.96.125", "144.202.96.125"));
		vSeeds.push_back(CDNSSeedData("80.208.228.48", "80.208.228.48"));
		vSeeds.push_back(CDNSSeedData("66.42.86.251", "66.42.86.251"));
		vSeeds.push_back(CDNSSeedData("207.246.93.18", "207.246.93.18"));
		vSeeds.push_back(CDNSSeedData("47.98.142.163", "47.98.142.163"));
		vSeeds.push_back(CDNSSeedData("45.32.153.239", "45.32.153.239"));
		vSeeds.push_back(CDNSSeedData("89.40.6.222", "89.40.6.222"));
		vSeeds.push_back(CDNSSeedData("89.47.160.181", "89.47.160.181"));
		vSeeds.push_back(CDNSSeedData("89.40.2.62", "89.40.2.62"));
		vSeeds.push_back(CDNSSeedData("83.217.206.155", "83.217.206.155"));
		vSeeds.push_back(CDNSSeedData("45.63.68.71", "45.63.68.71"));
		vSeeds.push_back(CDNSSeedData("47.92.155.26", "47.92.155.26"));
		vSeeds.push_back(CDNSSeedData("62.77.155.194", "62.77.155.194"));
		vSeeds.push_back(CDNSSeedData("158.69.216.59", "158.69.216.59"));
		vSeeds.push_back(CDNSSeedData("89.40.1.87", "89.40.1.87"));
		vSeeds.push_back(CDNSSeedData("45.32.145.134", "45.32.145.134"));
		vSeeds.push_back(CDNSSeedData("45.77.60.44", "45.77.60.44"));
		vSeeds.push_back(CDNSSeedData("95.179.161.232", "95.179.161.232"));
		vSeeds.push_back(CDNSSeedData("62.77.155.203", "62.77.155.203"));
		vSeeds.push_back(CDNSSeedData("172.245.241.147", "172.245.241.147"));
		vSeeds.push_back(CDNSSeedData("120.27.234.36", "120.27.234.36"));
		vSeeds.push_back(CDNSSeedData("51.15.240.222", "51.15.240.222"));
		vSeeds.push_back(CDNSSeedData("45.77.47.80", "45.77.47.80"));
		vSeeds.push_back(CDNSSeedData("43.224.34.191", "43.224.34.191"));
		vSeeds.push_back(CDNSSeedData("192.99.25.247", "192.99.25.247"));
		vSeeds.push_back(CDNSSeedData("108.61.117.143", "108.61.117.143"));
		vSeeds.push_back(CDNSSeedData("195.181.241.194", "195.181.241.194"));
		vSeeds.push_back(CDNSSeedData("45.76.90.191", "45.76.90.191"));
		vSeeds.push_back(CDNSSeedData("45.32.110.144", "45.32.110.144"));
		vSeeds.push_back(CDNSSeedData("89.40.4.115", "89.40.4.115"));
		vSeeds.push_back(CDNSSeedData("45.77.29.167", "45.77.29.167"));
		vSeeds.push_back(CDNSSeedData("198.13.38.215", "198.13.38.215"));
		vSeeds.push_back(CDNSSeedData("89.40.11.139", "89.40.11.139"));
		vSeeds.push_back(CDNSSeedData("173.232.224.62", "173.232.224.62"));
		vSeeds.push_back(CDNSSeedData("199.247.30.67", "199.247.30.67"));
		vSeeds.push_back(CDNSSeedData("80.209.236.187", "80.209.236.187"));
		vSeeds.push_back(CDNSSeedData("207.148.95.205", "207.148.95.205"));
		vSeeds.push_back(CDNSSeedData("69.165.192.43", "69.165.192.43"));
		vSeeds.push_back(CDNSSeedData("89.47.164.163", "89.47.164.163"));
		vSeeds.push_back(CDNSSeedData("47.92.137.156", "47.92.137.156"));
		vSeeds.push_back(CDNSSeedData("80.211.44.239", "80.211.44.239"));
		vSeeds.push_back(CDNSSeedData("207.246.86.252", "207.246.86.252"));
		vSeeds.push_back(CDNSSeedData("79.98.29.169", "79.98.29.169"));
		vSeeds.push_back(CDNSSeedData("159.65.225.3", "159.65.225.3"));
		vSeeds.push_back(CDNSSeedData("45.77.7.72", "45.77.7.72"));
		vSeeds.push_back(CDNSSeedData("198.13.60.207", "198.13.60.207"));
		vSeeds.push_back(CDNSSeedData("144.202.108.112", "144.202.108.112"));
		vSeeds.push_back(CDNSSeedData("45.32.157.139", "45.32.157.139"));
		vSeeds.push_back(CDNSSeedData("45.63.109.5", "45.63.109.5"));
		vSeeds.push_back(CDNSSeedData("95.179.141.52", "95.179.141.52"));
		vSeeds.push_back(CDNSSeedData("176.223.134.39", "176.223.134.39"));
		vSeeds.push_back(CDNSSeedData("89.40.8.75", "89.40.8.75"));
		vSeeds.push_back(CDNSSeedData("45.77.158.186", "45.77.158.186"));
		vSeeds.push_back(CDNSSeedData("199.247.30.95", "199.247.30.95"));
		vSeeds.push_back(CDNSSeedData("89.47.163.168", "89.47.163.168"));
		vSeeds.push_back(CDNSSeedData("89.47.164.10", "89.47.164.10"));
		vSeeds.push_back(CDNSSeedData("80.211.19.209", "80.211.19.209"));
		vSeeds.push_back(CDNSSeedData("95.179.136.183", "95.179.136.183"));
		vSeeds.push_back(CDNSSeedData("176.223.129.129", "176.223.129.129"));
		vSeeds.push_back(CDNSSeedData("45.76.82.96", "45.76.82.96"));
		vSeeds.push_back(CDNSSeedData("51.15.196.154", "51.15.196.154"));
		vSeeds.push_back(CDNSSeedData("80.209.239.34", "80.209.239.34"));
		vSeeds.push_back(CDNSSeedData("222.191.227.122", "222.191.227.122"));
		vSeeds.push_back(CDNSSeedData("185.22.152.169", "185.22.152.169"));
		vSeeds.push_back(CDNSSeedData("172.245.241.119", "172.245.241.119"));
		vSeeds.push_back(CDNSSeedData("45.77.182.178", "45.77.182.178"));
		vSeeds.push_back(CDNSSeedData("176.223.133.133", "176.223.133.133"));
		vSeeds.push_back(CDNSSeedData("62.77.152.127", "62.77.152.127"));
		vSeeds.push_back(CDNSSeedData("62.77.156.100", "62.77.156.100"));
		vSeeds.push_back(CDNSSeedData("45.32.226.255", "45.32.226.255"));
		vSeeds.push_back(CDNSSeedData("176.223.129.198", "176.223.129.198"));
		vSeeds.push_back(CDNSSeedData("212.237.26.159", "212.237.26.159"));
		vSeeds.push_back(CDNSSeedData("45.32.223.75", "45.32.223.75"));
		vSeeds.push_back(CDNSSeedData("80.240.29.92", "80.240.29.92"));
		vSeeds.push_back(CDNSSeedData("80.209.224.27", "80.209.224.27"));
		vSeeds.push_back(CDNSSeedData("144.202.29.7", "144.202.29.7"));
		vSeeds.push_back(CDNSSeedData("176.223.134.245", "176.223.134.245"));
		vSeeds.push_back(CDNSSeedData("195.181.240.64", "195.181.240.64"));
		vSeeds.push_back(CDNSSeedData("185.5.54.53", "185.5.54.53"));
		vSeeds.push_back(CDNSSeedData("178.33.144.81", "178.33.144.81"));
		vSeeds.push_back(CDNSSeedData("80.208.225.120", "80.208.225.120"));
		vSeeds.push_back(CDNSSeedData("195.201.37.236", "195.201.37.236"));
		vSeeds.push_back(CDNSSeedData("89.40.13.69", "89.40.13.69"));
		vSeeds.push_back(CDNSSeedData("120.79.95.98", "120.79.95.98"));
		vSeeds.push_back(CDNSSeedData("135.23.195.167", "135.23.195.167"));
		vSeeds.push_back(CDNSSeedData("45.32.76.147", "45.32.76.147"));
		vSeeds.push_back(CDNSSeedData("165.227.73.108", "165.227.73.108"));
		vSeeds.push_back(CDNSSeedData("206.217.143.82", "206.217.143.82"));
		vSeeds.push_back(CDNSSeedData("47.92.67.56", "47.92.67.56"));
		vSeeds.push_back(CDNSSeedData("45.76.28.77", "45.76.28.77"));
		vSeeds.push_back(CDNSSeedData("80.209.237.211", "80.209.237.211"));
		vSeeds.push_back(CDNSSeedData("80.209.235.63", "80.209.235.63"));
		vSeeds.push_back(CDNSSeedData("80.209.225.94", "80.209.225.94"));
		vSeeds.push_back(CDNSSeedData("89.40.13.173", "89.40.13.173"));
		vSeeds.push_back(CDNSSeedData("80.240.17.177", "80.240.17.177"));
		vSeeds.push_back(CDNSSeedData("104.156.246.208", "104.156.246.208"));
		vSeeds.push_back(CDNSSeedData("207.148.20.153", "207.148.20.153"));
		vSeeds.push_back(CDNSSeedData("212.237.16.22", "212.237.16.22"));
		vSeeds.push_back(CDNSSeedData("47.92.4.153", "47.92.4.153"));
		vSeeds.push_back(CDNSSeedData("80.240.23.181", "80.240.23.181"));
		vSeeds.push_back(CDNSSeedData("45.77.112.253", "45.77.112.253"));
		vSeeds.push_back(CDNSSeedData("45.77.56.253", "45.77.56.253"));
		vSeeds.push_back(CDNSSeedData("176.223.138.164", "176.223.138.164"));
		vSeeds.push_back(CDNSSeedData("45.77.90.228", "45.77.90.228"));
		vSeeds.push_back(CDNSSeedData("45.32.226.192", "45.32.226.192"));
		vSeeds.push_back(CDNSSeedData("38.127.169.152", "38.127.169.152"));
		vSeeds.push_back(CDNSSeedData("176.223.140.54", "176.223.140.54"));
		vSeeds.push_back(CDNSSeedData("45.76.82.167", "45.76.82.167"));
		vSeeds.push_back(CDNSSeedData("45.76.86.52", "45.76.86.52"));
		vSeeds.push_back(CDNSSeedData("80.208.230.112", "80.208.230.112"));
		vSeeds.push_back(CDNSSeedData("89.47.162.198", "89.47.162.198"));
		vSeeds.push_back(CDNSSeedData("47.92.2.232", "47.92.2.232"));
		vSeeds.push_back(CDNSSeedData("62.77.157.55", "62.77.157.55"));
		vSeeds.push_back(CDNSSeedData("89.47.165.169", "89.47.165.169"));
		vSeeds.push_back(CDNSSeedData("45.76.56.89", "45.76.56.89"));
		vSeeds.push_back(CDNSSeedData("108.61.221.227", "108.61.221.227"));
		vSeeds.push_back(CDNSSeedData("104.223.96.150", "104.223.96.150"));
		vSeeds.push_back(CDNSSeedData("62.77.159.5", "62.77.159.5"));
		vSeeds.push_back(CDNSSeedData("64.154.38.181", "64.154.38.181"));
		vSeeds.push_back(CDNSSeedData("45.32.149.139", "45.32.149.139"));
		vSeeds.push_back(CDNSSeedData("140.82.51.42", "140.82.51.42"));
		vSeeds.push_back(CDNSSeedData("209.250.247.31", "209.250.247.31"));
		vSeeds.push_back(CDNSSeedData("47.92.122.226", "47.92.122.226"));
		vSeeds.push_back(CDNSSeedData("80.209.235.4", "80.209.235.4"));
		vSeeds.push_back(CDNSSeedData("104.238.162.102", "104.238.162.102"));
		vSeeds.push_back(CDNSSeedData("80.209.239.71", "80.209.239.71"));
		vSeeds.push_back(CDNSSeedData("18.195.200.103", "18.195.200.103"));
		vSeeds.push_back(CDNSSeedData("149.28.195.96", "149.28.195.96"));
		vSeeds.push_back(CDNSSeedData("38.127.169.153", "38.127.169.153"));
		vSeeds.push_back(CDNSSeedData("176.223.128.126", "176.223.128.126"));
		vSeeds.push_back(CDNSSeedData("185.233.107.0", "185.233.107.0"));
		vSeeds.push_back(CDNSSeedData("45.77.251.99", "45.77.251.99"));
		vSeeds.push_back(CDNSSeedData("62.77.155.201", "62.77.155.201"));
		vSeeds.push_back(CDNSSeedData("107.172.252.236", "107.172.252.236"));
		vSeeds.push_back(CDNSSeedData("89.40.11.189", "89.40.11.189"));
		vSeeds.push_back(CDNSSeedData("207.148.31.37", "207.148.31.37"));
		vSeeds.push_back(CDNSSeedData("195.181.242.124", "195.181.242.124"));
		vSeeds.push_back(CDNSSeedData("45.76.134.105", "45.76.134.105"));
		vSeeds.push_back(CDNSSeedData("149.28.61.70", "149.28.61.70"));
		vSeeds.push_back(CDNSSeedData("80.208.230.191", "80.208.230.191"));
		vSeeds.push_back(CDNSSeedData("95.179.152.112", "95.179.152.112"));
		vSeeds.push_back(CDNSSeedData("89.47.164.148", "89.47.164.148"));
		vSeeds.push_back(CDNSSeedData("176.223.132.216", "176.223.132.216"));
		vSeeds.push_back(CDNSSeedData("195.181.240.182", "195.181.240.182"));
		vSeeds.push_back(CDNSSeedData("89.47.161.24", "89.47.161.24"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("188.201.198.114", "188.201.198.114"));
		vSeeds.push_back(CDNSSeedData("89.47.165.199", "89.47.165.199"));
		vSeeds.push_back(CDNSSeedData("23.94.189.10", "23.94.189.10"));
		vSeeds.push_back(CDNSSeedData("89.40.8.35", "89.40.8.35"));
		vSeeds.push_back(CDNSSeedData("86.121.208.47", "86.121.208.47"));
		vSeeds.push_back(CDNSSeedData("138.68.189.96", "138.68.189.96"));
		vSeeds.push_back(CDNSSeedData("89.47.163.71", "89.47.163.71"));
		vSeeds.push_back(CDNSSeedData("45.77.4.43", "45.77.4.43"));
		vSeeds.push_back(CDNSSeedData("54.162.25.185", "54.162.25.185"));
		vSeeds.push_back(CDNSSeedData("80.209.231.73", "80.209.231.73"));
		vSeeds.push_back(CDNSSeedData("45.77.186.101", "45.77.186.101"));
		vSeeds.push_back(CDNSSeedData("104.238.158.13", "104.238.158.13"));
		vSeeds.push_back(CDNSSeedData("176.223.132.18", "176.223.132.18"));
		vSeeds.push_back(CDNSSeedData("195.181.240.170", "195.181.240.170"));
		vSeeds.push_back(CDNSSeedData("176.223.132.129", "176.223.132.129"));
		vSeeds.push_back(CDNSSeedData("176.223.131.243", "176.223.131.243"));
		vSeeds.push_back(CDNSSeedData("62.77.155.192", "62.77.155.192"));
		vSeeds.push_back(CDNSSeedData("45.77.19.76", "45.77.19.76"));
		vSeeds.push_back(CDNSSeedData("194.135.83.13", "194.135.83.13"));
		vSeeds.push_back(CDNSSeedData("45.77.53.48", "45.77.53.48"));
		vSeeds.push_back(CDNSSeedData("51.255.169.161", "51.255.169.161"));
		vSeeds.push_back(CDNSSeedData("45.76.87.76", "45.76.87.76"));
		vSeeds.push_back(CDNSSeedData("45.32.221.191", "45.32.221.191"));
		vSeeds.push_back(CDNSSeedData("104.238.180.35", "104.238.180.35"));
		vSeeds.push_back(CDNSSeedData("195.181.247.27", "195.181.247.27"));
		vSeeds.push_back(CDNSSeedData("188.68.45.227", "188.68.45.227"));
		vSeeds.push_back(CDNSSeedData("207.246.87.163", "207.246.87.163"));
		vSeeds.push_back(CDNSSeedData("209.250.247.158", "209.250.247.158"));
		vSeeds.push_back(CDNSSeedData("185.216.27.100", "185.216.27.100"));
		vSeeds.push_back(CDNSSeedData("89.40.11.243", "89.40.11.243"));
		vSeeds.push_back(CDNSSeedData("94.16.112.166", "94.16.112.166"));
		vSeeds.push_back(CDNSSeedData("45.77.200.171", "45.77.200.171"));
		vSeeds.push_back(CDNSSeedData("80.208.231.174", "80.208.231.174"));
		vSeeds.push_back(CDNSSeedData("45.77.200.163", "45.77.200.163"));
		vSeeds.push_back(CDNSSeedData("173.249.14.246", "173.249.14.246"));
		vSeeds.push_back(CDNSSeedData("212.24.98.225", "212.24.98.225"));
		vSeeds.push_back(CDNSSeedData("149.28.245.36", "149.28.245.36"));
		vSeeds.push_back(CDNSSeedData("45.32.206.154", "45.32.206.154"));
		vSeeds.push_back(CDNSSeedData("47.92.24.21", "47.92.24.21"));
		vSeeds.push_back(CDNSSeedData("89.47.164.8", "89.47.164.8"));
		vSeeds.push_back(CDNSSeedData("45.77.57.45", "45.77.57.45"));
		vSeeds.push_back(CDNSSeedData("185.5.55.168", "185.5.55.168"));
		vSeeds.push_back(CDNSSeedData("62.77.158.101", "62.77.158.101"));
		vSeeds.push_back(CDNSSeedData("207.148.10.91", "207.148.10.91"));
		vSeeds.push_back(CDNSSeedData("80.209.228.130", "80.209.228.130"));
		vSeeds.push_back(CDNSSeedData("159.69.30.120", "159.69.30.120"));
		vSeeds.push_back(CDNSSeedData("89.40.1.168", "89.40.1.168"));
		vSeeds.push_back(CDNSSeedData("176.223.142.248", "176.223.142.248"));
		vSeeds.push_back(CDNSSeedData("81.169.157.127", "81.169.157.127"));
		vSeeds.push_back(CDNSSeedData("174.112.209.127", "174.112.209.127"));
		vSeeds.push_back(CDNSSeedData("149.28.142.94", "149.28.142.94"));
		vSeeds.push_back(CDNSSeedData("149.28.232.103", "149.28.232.103"));
		vSeeds.push_back(CDNSSeedData("199.247.15.7", "199.247.15.7"));
		vSeeds.push_back(CDNSSeedData("198.58.100.227", "198.58.100.227"));
		vSeeds.push_back(CDNSSeedData("144.202.45.254", "144.202.45.254"));
		vSeeds.push_back(CDNSSeedData("104.238.158.92", "104.238.158.92"));
		vSeeds.push_back(CDNSSeedData("80.209.234.188", "80.209.234.188"));
		vSeeds.push_back(CDNSSeedData("199.247.7.56", "199.247.7.56"));
		vSeeds.push_back(CDNSSeedData("45.32.136.85", "45.32.136.85"));
		vSeeds.push_back(CDNSSeedData("89.40.8.76", "89.40.8.76"));
		vSeeds.push_back(CDNSSeedData("45.63.92.175", "45.63.92.175"));
		vSeeds.push_back(CDNSSeedData("136.144.169.241", "136.144.169.241"));
		vSeeds.push_back(CDNSSeedData("163.172.215.222", "163.172.215.222"));
		vSeeds.push_back(CDNSSeedData("209.250.240.144", "209.250.240.144"));
		vSeeds.push_back(CDNSSeedData("80.208.224.92", "80.208.224.92"));
		vSeeds.push_back(CDNSSeedData("62.77.152.16", "62.77.152.16"));
		vSeeds.push_back(CDNSSeedData("103.57.209.84", "103.57.209.84"));
		vSeeds.push_back(CDNSSeedData("149.210.194.73", "149.210.194.73"));
		vSeeds.push_back(CDNSSeedData("46.38.230.182", "46.38.230.182"));
		vSeeds.push_back(CDNSSeedData("159.65.84.87", "159.65.84.87"));
		vSeeds.push_back(CDNSSeedData("199.180.114.2", "199.180.114.2"));
		vSeeds.push_back(CDNSSeedData("89.40.2.33", "89.40.2.33"));
		vSeeds.push_back(CDNSSeedData("104.238.173.130", "104.238.173.130"));
		vSeeds.push_back(CDNSSeedData("194.135.89.133", "194.135.89.133"));
		vSeeds.push_back(CDNSSeedData("199.247.23.27", "199.247.23.27"));
		vSeeds.push_back(CDNSSeedData("89.40.1.203", "89.40.1.203"));
		vSeeds.push_back(CDNSSeedData("89.40.7.26", "89.40.7.26"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("199.247.17.36", "199.247.17.36"));
		vSeeds.push_back(CDNSSeedData("47.92.173.238", "47.92.173.238"));
		vSeeds.push_back(CDNSSeedData("89.40.4.30", "89.40.4.30"));
		vSeeds.push_back(CDNSSeedData("47.92.2.189", "47.92.2.189"));
		vSeeds.push_back(CDNSSeedData("209.250.243.233", "209.250.243.233"));
		vSeeds.push_back(CDNSSeedData("195.181.242.146", "195.181.242.146"));
		vSeeds.push_back(CDNSSeedData("37.97.161.74", "37.97.161.74"));
		vSeeds.push_back(CDNSSeedData("66.175.211.5", "66.175.211.5"));
		vSeeds.push_back(CDNSSeedData("45.77.63.104", "45.77.63.104"));
		vSeeds.push_back(CDNSSeedData("45.77.140.40", "45.77.140.40"));
		vSeeds.push_back(CDNSSeedData("104.156.255.69", "104.156.255.69"));
		vSeeds.push_back(CDNSSeedData("104.131.101.153", "104.131.101.153"));
		vSeeds.push_back(CDNSSeedData("80.209.224.138", "80.209.224.138"));
		vSeeds.push_back(CDNSSeedData("89.40.2.100", "89.40.2.100"));
		vSeeds.push_back(CDNSSeedData("89.40.11.141", "89.40.11.141"));
		vSeeds.push_back(CDNSSeedData("176.223.131.126", "176.223.131.126"));
		vSeeds.push_back(CDNSSeedData("149.28.102.4", "149.28.102.4"));
		vSeeds.push_back(CDNSSeedData("195.181.213.212", "195.181.213.212"));
		vSeeds.push_back(CDNSSeedData("45.32.23.79", "45.32.23.79"));
		vSeeds.push_back(CDNSSeedData("104.156.226.42", "104.156.226.42"));
		vSeeds.push_back(CDNSSeedData("176.223.131.96", "176.223.131.96"));
		vSeeds.push_back(CDNSSeedData("45.77.56.222", "45.77.56.222"));
		vSeeds.push_back(CDNSSeedData("68.232.175.22", "68.232.175.22"));
		vSeeds.push_back(CDNSSeedData("62.77.159.4", "62.77.159.4"));
		vSeeds.push_back(CDNSSeedData("140.82.1.85", "140.82.1.85"));
		vSeeds.push_back(CDNSSeedData("45.77.21.134", "45.77.21.134"));
		vSeeds.push_back(CDNSSeedData("89.47.167.165", "89.47.167.165"));
		vSeeds.push_back(CDNSSeedData("80.208.228.216", "80.208.228.216"));
		vSeeds.push_back(CDNSSeedData("167.114.113.213", "167.114.113.213"));
		vSeeds.push_back(CDNSSeedData("47.74.226.15", "47.74.226.15"));
		vSeeds.push_back(CDNSSeedData("47.92.95.9", "47.92.95.9"));
		vSeeds.push_back(CDNSSeedData("89.47.160.242", "89.47.160.242"));
		vSeeds.push_back(CDNSSeedData("104.156.226.182", "104.156.226.182"));
		vSeeds.push_back(CDNSSeedData("217.182.209.139", "217.182.209.139"));
		vSeeds.push_back(CDNSSeedData("38.103.14.23", "38.103.14.23"));
		vSeeds.push_back(CDNSSeedData("45.77.191.9", "45.77.191.9"));
		vSeeds.push_back(CDNSSeedData("45.63.74.195", "45.63.74.195"));
		vSeeds.push_back(CDNSSeedData("94.130.174.218", "94.130.174.218"));
		vSeeds.push_back(CDNSSeedData("62.77.153.21", "62.77.153.21"));
		vSeeds.push_back(CDNSSeedData("62.77.156.96", "62.77.156.96"));
		vSeeds.push_back(CDNSSeedData("62.77.155.195", "62.77.155.195"));
		vSeeds.push_back(CDNSSeedData("104.207.143.169", "104.207.143.169"));
		vSeeds.push_back(CDNSSeedData("144.202.83.93", "144.202.83.93"));
		vSeeds.push_back(CDNSSeedData("89.40.15.84", "89.40.15.84"));
		vSeeds.push_back(CDNSSeedData("159.89.176.23", "159.89.176.23"));
		vSeeds.push_back(CDNSSeedData("45.76.183.164", "45.76.183.164"));
		vSeeds.push_back(CDNSSeedData("89.47.163.69", "89.47.163.69"));
		vSeeds.push_back(CDNSSeedData("144.202.111.139", "144.202.111.139"));
		vSeeds.push_back(CDNSSeedData("80.211.191.188", "80.211.191.188"));
		vSeeds.push_back(CDNSSeedData("23.94.137.144", "23.94.137.144"));
		vSeeds.push_back(CDNSSeedData("80.211.30.243", "80.211.30.243"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("69.164.192.137", "69.164.192.137"));
		vSeeds.push_back(CDNSSeedData("54.173.252.135", "54.173.252.135"));
		vSeeds.push_back(CDNSSeedData("89.40.2.59", "89.40.2.59"));
		vSeeds.push_back(CDNSSeedData("94.176.233.84", "94.176.233.84"));
		vSeeds.push_back(CDNSSeedData("212.24.110.63", "212.24.110.63"));
		vSeeds.push_back(CDNSSeedData("51.15.218.218", "51.15.218.218"));
		vSeeds.push_back(CDNSSeedData("89.40.11.244", "89.40.11.244"));
		vSeeds.push_back(CDNSSeedData("45.32.7.81", "45.32.7.81"));
		vSeeds.push_back(CDNSSeedData("46.101.248.213", "46.101.248.213"));
		vSeeds.push_back(CDNSSeedData("89.47.167.160", "89.47.167.160"));
		vSeeds.push_back(CDNSSeedData("167.99.205.80", "167.99.205.80"));
		vSeeds.push_back(CDNSSeedData("128.199.215.227", "128.199.215.227"));
		vSeeds.push_back(CDNSSeedData("80.209.226.48", "80.209.226.48"));
		vSeeds.push_back(CDNSSeedData("140.82.53.210", "140.82.53.210"));
		vSeeds.push_back(CDNSSeedData("149.28.174.233", "149.28.174.233"));
		vSeeds.push_back(CDNSSeedData("62.77.156.94", "62.77.156.94"));
		vSeeds.push_back(CDNSSeedData("89.40.14.10", "89.40.14.10"));
		vSeeds.push_back(CDNSSeedData("45.77.170.150", "45.77.170.150"));
		vSeeds.push_back(CDNSSeedData("82.223.48.37", "82.223.48.37"));
		vSeeds.push_back(CDNSSeedData("38.103.14.25", "38.103.14.25"));
		vSeeds.push_back(CDNSSeedData("89.47.161.181", "89.47.161.181"));
		vSeeds.push_back(CDNSSeedData("209.250.227.66", "209.250.227.66"));
		vSeeds.push_back(CDNSSeedData("95.179.140.254", "95.179.140.254"));
		vSeeds.push_back(CDNSSeedData("140.82.34.43", "140.82.34.43"));
		vSeeds.push_back(CDNSSeedData("89.40.15.42", "89.40.15.42"));
		vSeeds.push_back(CDNSSeedData("38.127.169.141", "38.127.169.141"));
		vSeeds.push_back(CDNSSeedData("159.69.31.11", "159.69.31.11"));
		vSeeds.push_back(CDNSSeedData("144.202.80.86", "144.202.80.86"));
		vSeeds.push_back(CDNSSeedData("144.202.119.189", "144.202.119.189"));
		vSeeds.push_back(CDNSSeedData("89.40.10.71", "89.40.10.71"));
		vSeeds.push_back(CDNSSeedData("62.77.159.59", "62.77.159.59"));
		vSeeds.push_back(CDNSSeedData("207.148.92.136", "207.148.92.136"));
		vSeeds.push_back(CDNSSeedData("47.92.75.41", "47.92.75.41"));
		vSeeds.push_back(CDNSSeedData("95.179.144.227", "95.179.144.227"));
		vSeeds.push_back(CDNSSeedData("109.235.71.67", "109.235.71.67"));
		vSeeds.push_back(CDNSSeedData("62.77.158.196", "62.77.158.196"));
		vSeeds.push_back(CDNSSeedData("62.77.158.108", "62.77.158.108"));
		vSeeds.push_back(CDNSSeedData("89.40.1.33", "89.40.1.33"));
		vSeeds.push_back(CDNSSeedData("80.211.216.238", "80.211.216.238"));
		vSeeds.push_back(CDNSSeedData("62.77.158.201", "62.77.158.201"));
		vSeeds.push_back(CDNSSeedData("35.201.203.32", "35.201.203.32"));
		vSeeds.push_back(CDNSSeedData("39.104.103.48", "39.104.103.48"));
		vSeeds.push_back(CDNSSeedData("45.76.90.53", "45.76.90.53"));
		vSeeds.push_back(CDNSSeedData("62.77.157.11", "62.77.157.11"));
		vSeeds.push_back(CDNSSeedData("172.104.246.190", "172.104.246.190"));
		vSeeds.push_back(CDNSSeedData("45.63.70.247", "45.63.70.247"));
		vSeeds.push_back(CDNSSeedData("80.209.229.83", "80.209.229.83"));
		vSeeds.push_back(CDNSSeedData("185.204.216.62", "185.204.216.62"));
		vSeeds.push_back(CDNSSeedData("45.76.55.184", "45.76.55.184"));
		vSeeds.push_back(CDNSSeedData("45.77.62.54", "45.77.62.54"));
		vSeeds.push_back(CDNSSeedData("209.250.249.131", "209.250.249.131"));
		vSeeds.push_back(CDNSSeedData("54.37.157.60", "54.37.157.60"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("104.156.232.219", "104.156.232.219"));
		vSeeds.push_back(CDNSSeedData("209.250.239.14", "209.250.239.14"));
		vSeeds.push_back(CDNSSeedData("80.209.235.87", "80.209.235.87"));
		vSeeds.push_back(CDNSSeedData("211.62.180.24", "211.62.180.24"));
		vSeeds.push_back(CDNSSeedData("62.138.18.245", "62.138.18.245"));
		vSeeds.push_back(CDNSSeedData("94.16.122.215", "94.16.122.215"));
		vSeeds.push_back(CDNSSeedData("80.208.225.15", "80.208.225.15"));
		vSeeds.push_back(CDNSSeedData("89.40.15.83", "89.40.15.83"));
		vSeeds.push_back(CDNSSeedData("159.69.39.188", "159.69.39.188"));
		vSeeds.push_back(CDNSSeedData("79.98.31.172", "79.98.31.172"));
		vSeeds.push_back(CDNSSeedData("185.81.167.156", "185.81.167.156"));
		vSeeds.push_back(CDNSSeedData("80.209.232.124", "80.209.232.124"));
		vSeeds.push_back(CDNSSeedData("34.254.176.143", "34.254.176.143"));
		vSeeds.push_back(CDNSSeedData("45.63.43.200", "45.63.43.200"));
		vSeeds.push_back(CDNSSeedData("80.211.56.18", "80.211.56.18"));
		vSeeds.push_back(CDNSSeedData("62.77.154.92", "62.77.154.92"));
		vSeeds.push_back(CDNSSeedData("217.182.252.235", "217.182.252.235"));
		vSeeds.push_back(CDNSSeedData("42.32.89.234", "42.32.89.234"));
		vSeeds.push_back(CDNSSeedData("207.246.93.137", "207.246.93.137"));
		vSeeds.push_back(CDNSSeedData("80.209.239.242", "80.209.239.242"));
		vSeeds.push_back(CDNSSeedData("50.3.81.104", "50.3.81.104"));
		vSeeds.push_back(CDNSSeedData("209.250.242.147", "209.250.242.147"));
		vSeeds.push_back(CDNSSeedData("139.59.87.20", "139.59.87.20"));
		vSeeds.push_back(CDNSSeedData("108.61.23.55", "108.61.23.55"));
		vSeeds.push_back(CDNSSeedData("89.47.165.155", "89.47.165.155"));
		vSeeds.push_back(CDNSSeedData("199.247.1.248", "199.247.1.248"));
		vSeeds.push_back(CDNSSeedData("80.208.225.158", "80.208.225.158"));
		vSeeds.push_back(CDNSSeedData("80.208.228.214", "80.208.228.214"));
		vSeeds.push_back(CDNSSeedData("89.40.15.154", "89.40.15.154"));
		vSeeds.push_back(CDNSSeedData("62.77.155.40", "62.77.155.40"));
		vSeeds.push_back(CDNSSeedData("80.211.83.244", "80.211.83.244"));
		vSeeds.push_back(CDNSSeedData("163.172.156.114", "163.172.156.114"));
		vSeeds.push_back(CDNSSeedData("45.63.30.219", "45.63.30.219"));
		vSeeds.push_back(CDNSSeedData("195.181.241.141", "195.181.241.141"));
		vSeeds.push_back(CDNSSeedData("80.209.230.145", "80.209.230.145"));
		vSeeds.push_back(CDNSSeedData("79.98.28.238", "79.98.28.238"));
		vSeeds.push_back(CDNSSeedData("185.81.166.123", "185.81.166.123"));
		vSeeds.push_back(CDNSSeedData("91.211.248.219", "91.211.248.219"));
		vSeeds.push_back(CDNSSeedData("80.211.135.97", "80.211.135.97"));
		vSeeds.push_back(CDNSSeedData("138.197.222.131", "138.197.222.131"));
		vSeeds.push_back(CDNSSeedData("80.209.230.136", "80.209.230.136"));
		vSeeds.push_back(CDNSSeedData("66.42.49.203", "66.42.49.203"));
		vSeeds.push_back(CDNSSeedData("80.240.31.107", "80.240.31.107"));
		vSeeds.push_back(CDNSSeedData("140.82.0.133", "140.82.0.133"));
		vSeeds.push_back(CDNSSeedData("39.104.53.73", "39.104.53.73"));
		vSeeds.push_back(CDNSSeedData("89.40.3.87", "89.40.3.87"));
		vSeeds.push_back(CDNSSeedData("47.92.2.213", "47.92.2.213"));
		vSeeds.push_back(CDNSSeedData("47.88.51.78", "47.88.51.78"));
		vSeeds.push_back(CDNSSeedData("176.223.133.96", "176.223.133.96"));
		vSeeds.push_back(CDNSSeedData("89.40.12.225", "89.40.12.225"));
		vSeeds.push_back(CDNSSeedData("176.223.134.73", "176.223.134.73"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("159.89.94.240", "159.89.94.240"));
		vSeeds.push_back(CDNSSeedData("79.98.25.190", "79.98.25.190"));
		vSeeds.push_back(CDNSSeedData("95.179.128.102", "95.179.128.102"));
		vSeeds.push_back(CDNSSeedData("80.209.237.143", "80.209.237.143"));
		vSeeds.push_back(CDNSSeedData("185.204.3.177", "185.204.3.177"));
		vSeeds.push_back(CDNSSeedData("138.201.119.10", "138.201.119.10"));
		vSeeds.push_back(CDNSSeedData("95.179.143.223", "95.179.143.223"));
		vSeeds.push_back(CDNSSeedData("45.76.195.183", "45.76.195.183"));
		vSeeds.push_back(CDNSSeedData("89.40.13.172", "89.40.13.172"));
		vSeeds.push_back(CDNSSeedData("89.40.6.35", "89.40.6.35"));
		vSeeds.push_back(CDNSSeedData("160.19.48.213", "160.19.48.213"));
		vSeeds.push_back(CDNSSeedData("79.98.25.215", "79.98.25.215"));
		vSeeds.push_back(CDNSSeedData("80.240.16.206", "80.240.16.206"));
		vSeeds.push_back(CDNSSeedData("80.209.233.160", "80.209.233.160"));
		vSeeds.push_back(CDNSSeedData("85.25.251.199", "85.25.251.199"));
		vSeeds.push_back(CDNSSeedData("89.47.160.7", "89.47.160.7"));
		vSeeds.push_back(CDNSSeedData("107.174.245.47", "107.174.245.47"));
		vSeeds.push_back(CDNSSeedData("207.246.123.210", "207.246.123.210"));
		vSeeds.push_back(CDNSSeedData("89.47.161.109", "89.47.161.109"));
		vSeeds.push_back(CDNSSeedData("176.223.131.246", "176.223.131.246"));
		vSeeds.push_back(CDNSSeedData("80.209.227.164", "80.209.227.164"));
		vSeeds.push_back(CDNSSeedData("51.15.217.147", "51.15.217.147"));
		vSeeds.push_back(CDNSSeedData("45.76.136.51", "45.76.136.51"));
		vSeeds.push_back(CDNSSeedData("185.204.216.78", "185.204.216.78"));
		vSeeds.push_back(CDNSSeedData("66.42.80.30", "66.42.80.30"));
		vSeeds.push_back(CDNSSeedData("163.172.155.189", "163.172.155.189"));
		vSeeds.push_back(CDNSSeedData("212.24.103.174", "212.24.103.174"));
		vSeeds.push_back(CDNSSeedData("94.176.239.2", "94.176.239.2"));
		vSeeds.push_back(CDNSSeedData("89.40.6.97", "89.40.6.97"));
		vSeeds.push_back(CDNSSeedData("39.104.94.77", "39.104.94.77"));
		vSeeds.push_back(CDNSSeedData("207.246.76.103", "207.246.76.103"));
		vSeeds.push_back(CDNSSeedData("89.40.12.162", "89.40.12.162"));
		vSeeds.push_back(CDNSSeedData("176.223.142.5", "176.223.142.5"));
		vSeeds.push_back(CDNSSeedData("172.104.17.88", "172.104.17.88"));
		vSeeds.push_back(CDNSSeedData("89.40.13.136", "89.40.13.136"));
		vSeeds.push_back(CDNSSeedData("80.209.235.239", "80.209.235.239"));
		vSeeds.push_back(CDNSSeedData("80.209.238.124", "80.209.238.124"));
		vSeeds.push_back(CDNSSeedData("85.214.60.35", "85.214.60.35"));
		vSeeds.push_back(CDNSSeedData("128.199.173.214", "128.199.173.214"));
		vSeeds.push_back(CDNSSeedData("62.77.154.204", "62.77.154.204"));
		vSeeds.push_back(CDNSSeedData("176.31.43.131", "176.31.43.131"));
		vSeeds.push_back(CDNSSeedData("47.92.0.70", "47.92.0.70"));
		vSeeds.push_back(CDNSSeedData("222.186.172.39", "222.186.172.39"));
		vSeeds.push_back(CDNSSeedData("54.67.120.205", "54.67.120.205"));
		vSeeds.push_back(CDNSSeedData("149.28.136.226", "149.28.136.226"));
		vSeeds.push_back(CDNSSeedData("45.77.127.194", "45.77.127.194"));
		vSeeds.push_back(CDNSSeedData("62.77.155.199", "62.77.155.199"));
		vSeeds.push_back(CDNSSeedData("84.47.129.117", "84.47.129.117"));
		vSeeds.push_back(CDNSSeedData("207.148.87.163", "207.148.87.163"));
		vSeeds.push_back(CDNSSeedData("173.212.230.73", "173.212.230.73"));
		vSeeds.push_back(CDNSSeedData("47.92.174.22", "47.92.174.22"));
		vSeeds.push_back(CDNSSeedData("138.68.189.146", "138.68.189.146"));
		vSeeds.push_back(CDNSSeedData("34.245.96.238", "34.245.96.238"));
		vSeeds.push_back(CDNSSeedData("194.135.82.243", "194.135.82.243"));
		vSeeds.push_back(CDNSSeedData("47.92.64.104", "47.92.64.104"));
		vSeeds.push_back(CDNSSeedData("89.40.6.142", "89.40.6.142"));
		vSeeds.push_back(CDNSSeedData("8.9.31.29", "8.9.31.29"));
		vSeeds.push_back(CDNSSeedData("212.237.28.186", "212.237.28.186"));
		vSeeds.push_back(CDNSSeedData("38.127.169.149", "38.127.169.149"));
		vSeeds.push_back(CDNSSeedData("176.223.135.148", "176.223.135.148"));
		vSeeds.push_back(CDNSSeedData("207.148.12.14", "207.148.12.14"));
		vSeeds.push_back(CDNSSeedData("62.77.152.2", "62.77.152.2"));
		vSeeds.push_back(CDNSSeedData("95.179.137.204", "95.179.137.204"));
		vSeeds.push_back(CDNSSeedData("85.88.29.170", "85.88.29.170"));
		vSeeds.push_back(CDNSSeedData("52.175.195.124", "52.175.195.124"));
		vSeeds.push_back(CDNSSeedData("209.250.235.127", "209.250.235.127"));
		vSeeds.push_back(CDNSSeedData("212.237.53.233", "212.237.53.233"));
		vSeeds.push_back(CDNSSeedData("140.82.36.172", "140.82.36.172"));
		vSeeds.push_back(CDNSSeedData("195.181.247.108", "195.181.247.108"));
		vSeeds.push_back(CDNSSeedData("89.40.2.183", "89.40.2.183"));
		vSeeds.push_back(CDNSSeedData("80.211.222.241", "80.211.222.241"));
		vSeeds.push_back(CDNSSeedData("144.202.55.150", "144.202.55.150"));
		vSeeds.push_back(CDNSSeedData("80.209.224.163", "80.209.224.163"));
		vSeeds.push_back(CDNSSeedData("149.56.14.246", "149.56.14.246"));
		vSeeds.push_back(CDNSSeedData("199.247.19.186", "199.247.19.186"));
		vSeeds.push_back(CDNSSeedData("80.211.22.48", "80.211.22.48"));
		vSeeds.push_back(CDNSSeedData("89.40.10.143", "89.40.10.143"));
		vSeeds.push_back(CDNSSeedData("89.47.160.10", "89.47.160.10"));
		vSeeds.push_back(CDNSSeedData("89.47.164.253", "89.47.164.253"));
		vSeeds.push_back(CDNSSeedData("89.40.6.145", "89.40.6.145"));
		vSeeds.push_back(CDNSSeedData("176.223.135.142", "176.223.135.142"));
		vSeeds.push_back(CDNSSeedData("51.15.208.11", "51.15.208.11"));
		vSeeds.push_back(CDNSSeedData("212.237.4.137", "212.237.4.137"));
		vSeeds.push_back(CDNSSeedData("209.250.253.131", "209.250.253.131"));
		vSeeds.push_back(CDNSSeedData("38.127.169.148", "38.127.169.148"));
		vSeeds.push_back(CDNSSeedData("176.223.141.7", "176.223.141.7"));
		vSeeds.push_back(CDNSSeedData("209.250.246.144", "209.250.246.144"));
		vSeeds.push_back(CDNSSeedData("94.176.238.26", "94.176.238.26"));
		vSeeds.push_back(CDNSSeedData("176.223.128.71", "176.223.128.71"));
		vSeeds.push_back(CDNSSeedData("108.61.211.104", "108.61.211.104"));
		vSeeds.push_back(CDNSSeedData("80.211.91.238", "80.211.91.238"));
		vSeeds.push_back(CDNSSeedData("47.254.27.87", "47.254.27.87"));
		vSeeds.push_back(CDNSSeedData("62.77.152.132", "62.77.152.132"));
		vSeeds.push_back(CDNSSeedData("107.191.48.187", "107.191.48.187"));
		vSeeds.push_back(CDNSSeedData("62.77.157.104", "62.77.157.104"));
		vSeeds.push_back(CDNSSeedData("95.179.133.196", "95.179.133.196"));
		vSeeds.push_back(CDNSSeedData("80.211.40.136", "80.211.40.136"));
		vSeeds.push_back(CDNSSeedData("174.127.79.206", "174.127.79.206"));
		vSeeds.push_back(CDNSSeedData("144.202.98.154", "144.202.98.154"));
		vSeeds.push_back(CDNSSeedData("54.205.98.42", "54.205.98.42"));
		vSeeds.push_back(CDNSSeedData("66.42.107.44", "66.42.107.44"));
		vSeeds.push_back(CDNSSeedData("89.47.166.65", "89.47.166.65"));
		vSeeds.push_back(CDNSSeedData("47.92.172.76", "47.92.172.76"));
		vSeeds.push_back(CDNSSeedData("45.76.32.121", "45.76.32.121"));
		vSeeds.push_back(CDNSSeedData("50.116.2.236", "50.116.2.236"));
		vSeeds.push_back(CDNSSeedData("47.254.133.104", "47.254.133.104"));
		vSeeds.push_back(CDNSSeedData("209.250.254.244", "209.250.254.244"));
		vSeeds.push_back(CDNSSeedData("62.77.153.24", "62.77.153.24"));
		vSeeds.push_back(CDNSSeedData("45.32.186.251", "45.32.186.251"));
		vSeeds.push_back(CDNSSeedData("89.40.15.152", "89.40.15.152"));
		vSeeds.push_back(CDNSSeedData("80.240.31.96", "80.240.31.96"));
		vSeeds.push_back(CDNSSeedData("95.179.130.60", "95.179.130.60"));
		vSeeds.push_back(CDNSSeedData("173.249.15.91", "173.249.15.91"));
		vSeeds.push_back(CDNSSeedData("95.179.156.92", "95.179.156.92"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("47.92.80.228", "47.92.80.228"));
		vSeeds.push_back(CDNSSeedData("89.47.163.224", "89.47.163.224"));
		vSeeds.push_back(CDNSSeedData("45.77.67.44", "45.77.67.44"));
		vSeeds.push_back(CDNSSeedData("149.28.178.212", "149.28.178.212"));
		vSeeds.push_back(CDNSSeedData("149.28.131.27", "149.28.131.27"));
		vSeeds.push_back(CDNSSeedData("95.179.136.64", "95.179.136.64"));
		vSeeds.push_back(CDNSSeedData("45.63.1.51", "45.63.1.51"));
		vSeeds.push_back(CDNSSeedData("45.32.187.143", "45.32.187.143"));
		vSeeds.push_back(CDNSSeedData("89.40.11.193", "89.40.11.193"));
		vSeeds.push_back(CDNSSeedData("46.38.241.37", "46.38.241.37"));
		vSeeds.push_back(CDNSSeedData("172.245.170.187", "172.245.170.187"));
		vSeeds.push_back(CDNSSeedData("194.135.80.28", "194.135.80.28"));
		vSeeds.push_back(CDNSSeedData("18.130.182.237", "18.130.182.237"));
		vSeeds.push_back(CDNSSeedData("45.76.128.226", "45.76.128.226"));
		vSeeds.push_back(CDNSSeedData("193.192.252.51", "193.192.252.51"));
		vSeeds.push_back(CDNSSeedData("89.40.15.215", "89.40.15.215"));
		vSeeds.push_back(CDNSSeedData("176.223.135.149", "176.223.135.149"));
		vSeeds.push_back(CDNSSeedData("144.202.60.140", "144.202.60.140"));
		vSeeds.push_back(CDNSSeedData("80.211.179.95", "80.211.179.95"));
		vSeeds.push_back(CDNSSeedData("149.28.182.33", "149.28.182.33"));
		vSeeds.push_back(CDNSSeedData("62.77.159.227", "62.77.159.227"));
		vSeeds.push_back(CDNSSeedData("38.127.169.131", "38.127.169.131"));
		vSeeds.push_back(CDNSSeedData("145.239.83.88", "145.239.83.88"));
		vSeeds.push_back(CDNSSeedData("149.28.32.2", "149.28.32.2"));
		vSeeds.push_back(CDNSSeedData("207.148.13.72", "207.148.13.72"));
		vSeeds.push_back(CDNSSeedData("89.40.3.83", "89.40.3.83"));
		vSeeds.push_back(CDNSSeedData("89.40.2.189", "89.40.2.189"));
		vSeeds.push_back(CDNSSeedData("45.76.103.53", "45.76.103.53"));
		vSeeds.push_back(CDNSSeedData("80.209.233.192", "80.209.233.192"));
		vSeeds.push_back(CDNSSeedData("195.181.244.131", "195.181.244.131"));
		vSeeds.push_back(CDNSSeedData("199.247.15.35", "199.247.15.35"));
		vSeeds.push_back(CDNSSeedData("45.32.150.182", "45.32.150.182"));
		vSeeds.push_back(CDNSSeedData("89.40.10.66", "89.40.10.66"));
		vSeeds.push_back(CDNSSeedData("51.15.130.236", "51.15.130.236"));
		vSeeds.push_back(CDNSSeedData("120.79.73.44", "120.79.73.44"));
		vSeeds.push_back(CDNSSeedData("108.61.178.134", "108.61.178.134"));
		vSeeds.push_back(CDNSSeedData("149.28.40.96", "149.28.40.96"));
		vSeeds.push_back(CDNSSeedData("89.47.160.92", "89.47.160.92"));
		vSeeds.push_back(CDNSSeedData("104.156.249.139", "104.156.249.139"));
		vSeeds.push_back(CDNSSeedData("89.47.160.87", "89.47.160.87"));
		vSeeds.push_back(CDNSSeedData("89.40.2.101", "89.40.2.101"));
		vSeeds.push_back(CDNSSeedData("216.244.80.124", "216.244.80.124"));
		vSeeds.push_back(CDNSSeedData("103.57.209.83", "103.57.209.83"));
		vSeeds.push_back(CDNSSeedData("51.254.219.224", "51.254.219.224"));
		vSeeds.push_back(CDNSSeedData("207.246.69.139", "207.246.69.139"));
		vSeeds.push_back(CDNSSeedData("80.209.236.207", "80.209.236.207"));
		vSeeds.push_back(CDNSSeedData("199.247.9.206", "199.247.9.206"));
		vSeeds.push_back(CDNSSeedData("35.234.17.253", "35.234.17.253"));
		vSeeds.push_back(CDNSSeedData("195.201.103.247", "195.201.103.247"));
		vSeeds.push_back(CDNSSeedData("80.209.233.254", "80.209.233.254"));
		vSeeds.push_back(CDNSSeedData("5.135.157.84", "5.135.157.84"));
		vSeeds.push_back(CDNSSeedData("51.38.234.243", "51.38.234.243"));
		vSeeds.push_back(CDNSSeedData("45.77.141.28", "45.77.141.28"));
		vSeeds.push_back(CDNSSeedData("45.76.62.199", "45.76.62.199"));
		vSeeds.push_back(CDNSSeedData("207.246.84.230", "207.246.84.230"));
		vSeeds.push_back(CDNSSeedData("80.209.236.175", "80.209.236.175"));
		vSeeds.push_back(CDNSSeedData("209.250.226.100", "209.250.226.100"));
		vSeeds.push_back(CDNSSeedData("195.201.103.245", "195.201.103.245"));
		vSeeds.push_back(CDNSSeedData("194.135.91.89", "194.135.91.89"));
		vSeeds.push_back(CDNSSeedData("82.195.236.149", "82.195.236.149"));
		vSeeds.push_back(CDNSSeedData("62.77.152.116", "62.77.152.116"));
		vSeeds.push_back(CDNSSeedData("163.172.182.237", "163.172.182.237"));
		vSeeds.push_back(CDNSSeedData("45.32.145.141", "45.32.145.141"));
		vSeeds.push_back(CDNSSeedData("80.209.224.68", "80.209.224.68"));
		vSeeds.push_back(CDNSSeedData("5.196.52.20", "5.196.52.20"));
		vSeeds.push_back(CDNSSeedData("104.238.179.180", "104.238.179.180"));
		vSeeds.push_back(CDNSSeedData("173.212.234.126", "173.212.234.126"));
		vSeeds.push_back(CDNSSeedData("207.246.118.160", "207.246.118.160"));
		vSeeds.push_back(CDNSSeedData("45.76.55.64", "45.76.55.64"));
		vSeeds.push_back(CDNSSeedData("45.76.39.235", "45.76.39.235"));
		vSeeds.push_back(CDNSSeedData("89.40.5.40", "89.40.5.40"));
		vSeeds.push_back(CDNSSeedData("95.179.139.212", "95.179.139.212"));
		vSeeds.push_back(CDNSSeedData("80.209.227.53", "80.209.227.53"));
		vSeeds.push_back(CDNSSeedData("95.179.150.41", "95.179.150.41"));
		vSeeds.push_back(CDNSSeedData("176.223.134.97", "176.223.134.97"));
		vSeeds.push_back(CDNSSeedData("45.32.144.59", "45.32.144.59"));
		vSeeds.push_back(CDNSSeedData("47.92.80.248", "47.92.80.248"));
		vSeeds.push_back(CDNSSeedData("140.82.59.224", "140.82.59.224"));
		vSeeds.push_back(CDNSSeedData("95.179.142.225", "95.179.142.225"));
		vSeeds.push_back(CDNSSeedData("89.47.163.169", "89.47.163.169"));
		vSeeds.push_back(CDNSSeedData("195.201.40.196", "195.201.40.196"));
		vSeeds.push_back(CDNSSeedData("80.209.229.88", "80.209.229.88"));
		vSeeds.push_back(CDNSSeedData("62.77.158.198", "62.77.158.198"));
		vSeeds.push_back(CDNSSeedData("198.58.107.5", "198.58.107.5"));
		vSeeds.push_back(CDNSSeedData("194.135.85.239", "194.135.85.239"));
		vSeeds.push_back(CDNSSeedData("207.148.29.201", "207.148.29.201"));
		vSeeds.push_back(CDNSSeedData("89.40.7.221", "89.40.7.221"));
		vSeeds.push_back(CDNSSeedData("95.181.179.106", "95.181.179.106"));
		vSeeds.push_back(CDNSSeedData("212.24.96.173", "212.24.96.173"));
		vSeeds.push_back(CDNSSeedData("35.174.138.169", "35.174.138.169"));
		vSeeds.push_back(CDNSSeedData("176.223.140.38", "176.223.140.38"));
		vSeeds.push_back(CDNSSeedData("89.40.5.42", "89.40.5.42"));
		vSeeds.push_back(CDNSSeedData("176.223.141.4", "176.223.141.4"));
		vSeeds.push_back(CDNSSeedData("80.208.231.136", "80.208.231.136"));
		vSeeds.push_back(CDNSSeedData("185.239.236.161", "185.239.236.161"));
		vSeeds.push_back(CDNSSeedData("104.156.245.108", "104.156.245.108"));
		vSeeds.push_back(CDNSSeedData("80.209.235.199", "80.209.235.199"));
		vSeeds.push_back(CDNSSeedData("80.209.227.24", "80.209.227.24"));
		vSeeds.push_back(CDNSSeedData("149.28.98.79", "149.28.98.79"));
		vSeeds.push_back(CDNSSeedData("85.88.29.189", "85.88.29.189"));
		vSeeds.push_back(CDNSSeedData("163.172.166.59", "163.172.166.59"));
		vSeeds.push_back(CDNSSeedData("45.76.47.23", "45.76.47.23"));
		vSeeds.push_back(CDNSSeedData("207.246.122.87", "207.246.122.87"));
		vSeeds.push_back(CDNSSeedData("89.40.15.41", "89.40.15.41"));
		vSeeds.push_back(CDNSSeedData("62.77.152.6", "62.77.152.6"));
		vSeeds.push_back(CDNSSeedData("80.209.225.247", "80.209.225.247"));
		vSeeds.push_back(CDNSSeedData("45.77.127.203", "45.77.127.203"));
		vSeeds.push_back(CDNSSeedData("89.40.1.197", "89.40.1.197"));
		vSeeds.push_back(CDNSSeedData("80.209.226.231", "80.209.226.231"));
		vSeeds.push_back(CDNSSeedData("139.162.185.124", "139.162.185.124"));
		vSeeds.push_back(CDNSSeedData("45.76.228.246", "45.76.228.246"));
		vSeeds.push_back(CDNSSeedData("212.47.229.156", "212.47.229.156"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("89.47.164.14", "89.47.164.14"));
		vSeeds.push_back(CDNSSeedData("45.76.65.9", "45.76.65.9"));
		vSeeds.push_back(CDNSSeedData("89.40.3.82", "89.40.3.82"));
		vSeeds.push_back(CDNSSeedData("195.181.246.67", "195.181.246.67"));
		vSeeds.push_back(CDNSSeedData("45.32.186.80", "45.32.186.80"));
		vSeeds.push_back(CDNSSeedData("45.63.95.54", "45.63.95.54"));
		vSeeds.push_back(CDNSSeedData("115.68.232.34", "115.68.232.34"));
		vSeeds.push_back(CDNSSeedData("45.77.202.95", "45.77.202.95"));
		vSeeds.push_back(CDNSSeedData("144.202.93.181", "144.202.93.181"));
		vSeeds.push_back(CDNSSeedData("51.15.140.243", "51.15.140.243"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("39.104.106.89", "39.104.106.89"));
		vSeeds.push_back(CDNSSeedData("194.182.80.150", "194.182.80.150"));
		vSeeds.push_back(CDNSSeedData("176.223.138.28", "176.223.138.28"));
		vSeeds.push_back(CDNSSeedData("45.77.74.78", "45.77.74.78"));
		vSeeds.push_back(CDNSSeedData("62.77.154.212", "62.77.154.212"));
		vSeeds.push_back(CDNSSeedData("80.209.227.86", "80.209.227.86"));
		vSeeds.push_back(CDNSSeedData("45.32.239.248", "45.32.239.248"));
		vSeeds.push_back(CDNSSeedData("5.45.102.121", "5.45.102.121"));
		vSeeds.push_back(CDNSSeedData("80.209.230.176", "80.209.230.176"));
		vSeeds.push_back(CDNSSeedData("80.240.26.252", "80.240.26.252"));
		vSeeds.push_back(CDNSSeedData("149.28.195.143", "149.28.195.143"));
		vSeeds.push_back(CDNSSeedData("89.40.13.170", "89.40.13.170"));
		vSeeds.push_back(CDNSSeedData("62.77.157.11", "62.77.157.11"));
		vSeeds.push_back(CDNSSeedData("173.249.9.123", "173.249.9.123"));
		vSeeds.push_back(CDNSSeedData("80.211.50.153", "80.211.50.153"));
		vSeeds.push_back(CDNSSeedData("89.40.11.132", "89.40.11.132"));
		vSeeds.push_back(CDNSSeedData("89.47.165.249", "89.47.165.249"));
		vSeeds.push_back(CDNSSeedData("80.211.7.201", "80.211.7.201"));
		vSeeds.push_back(CDNSSeedData("62.77.158.197", "62.77.158.197"));
		vSeeds.push_back(CDNSSeedData("149.28.183.231", "149.28.183.231"));
		vSeeds.push_back(CDNSSeedData("107.174.225.121", "107.174.225.121"));
		vSeeds.push_back(CDNSSeedData("207.246.92.237", "207.246.92.237"));
		vSeeds.push_back(CDNSSeedData("195.201.103.246", "195.201.103.246"));
		vSeeds.push_back(CDNSSeedData("207.246.93.11", "207.246.93.11"));
		vSeeds.push_back(CDNSSeedData("149.28.90.135", "149.28.90.135"));
		vSeeds.push_back(CDNSSeedData("211.118.211.37", "211.118.211.37"));
		vSeeds.push_back(CDNSSeedData("176.223.131.169", "176.223.131.169"));
		vSeeds.push_back(CDNSSeedData("207.148.76.33", "207.148.76.33"));
		vSeeds.push_back(CDNSSeedData("198.211.120.187", "198.211.120.187"));
		vSeeds.push_back(CDNSSeedData("34.207.239.68", "34.207.239.68"));
		vSeeds.push_back(CDNSSeedData("80.209.235.13", "80.209.235.13"));
		vSeeds.push_back(CDNSSeedData("89.40.5.45", "89.40.5.45"));
		vSeeds.push_back(CDNSSeedData("89.40.6.40", "89.40.6.40"));
		vSeeds.push_back(CDNSSeedData("144.202.101.48", "144.202.101.48"));
		vSeeds.push_back(CDNSSeedData("45.76.141.201", "45.76.141.201"));
		vSeeds.push_back(CDNSSeedData("89.40.10.19", "89.40.10.19"));
		vSeeds.push_back(CDNSSeedData("139.99.97.24", "139.99.97.24"));
		vSeeds.push_back(CDNSSeedData("209.250.236.66", "209.250.236.66"));
		vSeeds.push_back(CDNSSeedData("144.202.45.31", "144.202.45.31"));
		vSeeds.push_back(CDNSSeedData("89.40.5.188", "89.40.5.188"));
		vSeeds.push_back(CDNSSeedData("188.68.55.90", "188.68.55.90"));
		vSeeds.push_back(CDNSSeedData("149.28.130.19", "149.28.130.19"));
		vSeeds.push_back(CDNSSeedData("144.202.36.36", "144.202.36.36"));
		vSeeds.push_back(CDNSSeedData("45.32.239.203", "45.32.239.203"));
		vSeeds.push_back(CDNSSeedData("199.247.27.44", "199.247.27.44"));
		vSeeds.push_back(CDNSSeedData("185.243.9.86", "185.243.9.86"));
		vSeeds.push_back(CDNSSeedData("89.40.13.114", "89.40.13.114"));
		vSeeds.push_back(CDNSSeedData("80.209.228.122", "80.209.228.122"));
		vSeeds.push_back(CDNSSeedData("45.76.249.206", "45.76.249.206"));
		vSeeds.push_back(CDNSSeedData("209.250.241.2", "209.250.241.2"));
		vSeeds.push_back(CDNSSeedData("95.179.135.158", "95.179.135.158"));
		vSeeds.push_back(CDNSSeedData("206.189.165.232", "206.189.165.232"));
		vSeeds.push_back(CDNSSeedData("89.40.8.209", "89.40.8.209"));
		vSeeds.push_back(CDNSSeedData("104.168.94.77", "104.168.94.77"));
		vSeeds.push_back(CDNSSeedData("89.47.160.74", "89.47.160.74"));
		vSeeds.push_back(CDNSSeedData("62.77.154.94", "62.77.154.94"));
		vSeeds.push_back(CDNSSeedData("62.77.155.146", "62.77.155.146"));
		vSeeds.push_back(CDNSSeedData("176.223.131.126", "176.223.131.126"));
		vSeeds.push_back(CDNSSeedData("62.77.155.190", "62.77.155.190"));
		vSeeds.push_back(CDNSSeedData("89.47.161.188", "89.47.161.188"));
		vSeeds.push_back(CDNSSeedData("18.231.101.212", "18.231.101.212"));
		vSeeds.push_back(CDNSSeedData("89.40.3.177", "89.40.3.177"));
		vSeeds.push_back(CDNSSeedData("198.55.125.50", "198.55.125.50"));
		vSeeds.push_back(CDNSSeedData("80.211.175.170", "80.211.175.170"));
		vSeeds.push_back(CDNSSeedData("47.254.43.103", "47.254.43.103"));
		vSeeds.push_back(CDNSSeedData("144.202.56.188", "144.202.56.188"));
		vSeeds.push_back(CDNSSeedData("80.208.227.50", "80.208.227.50"));
		vSeeds.push_back(CDNSSeedData("176.223.131.126", "176.223.131.126"));
		vSeeds.push_back(CDNSSeedData("95.179.129.101", "95.179.129.101"));
		vSeeds.push_back(CDNSSeedData("45.32.154.196", "45.32.154.196"));
		vSeeds.push_back(CDNSSeedData("47.254.45.7", "47.254.45.7"));
		vSeeds.push_back(CDNSSeedData("104.168.126.44", "104.168.126.44"));
		vSeeds.push_back(CDNSSeedData("45.77.167.179", "45.77.167.179"));
		vSeeds.push_back(CDNSSeedData("89.47.160.76", "89.47.160.76"));
		vSeeds.push_back(CDNSSeedData("89.40.4.27", "89.40.4.27"));
		vSeeds.push_back(CDNSSeedData("207.148.8.136", "207.148.8.136"));
		vSeeds.push_back(CDNSSeedData("47.75.36.195", "47.75.36.195"));
		vSeeds.push_back(CDNSSeedData("94.176.238.216", "94.176.238.216"));
		vSeeds.push_back(CDNSSeedData("47.92.39.128", "47.92.39.128"));
		vSeeds.push_back(CDNSSeedData("62.77.156.92", "62.77.156.92"));
		vSeeds.push_back(CDNSSeedData("66.42.64.131", "66.42.64.131"));
		vSeeds.push_back(CDNSSeedData("54.37.67.210", "54.37.67.210"));
		vSeeds.push_back(CDNSSeedData("209.250.233.30", "209.250.233.30"));
		vSeeds.push_back(CDNSSeedData("144.202.96.45", "144.202.96.45"));
		vSeeds.push_back(CDNSSeedData("45.77.230.240", "45.77.230.240"));
		vSeeds.push_back(CDNSSeedData("209.250.224.42", "209.250.224.42"));
		vSeeds.push_back(CDNSSeedData("80.209.226.115", "80.209.226.115"));
		vSeeds.push_back(CDNSSeedData("62.77.153.156", "62.77.153.156"));
		vSeeds.push_back(CDNSSeedData("51.15.233.115", "51.15.233.115"));
		vSeeds.push_back(CDNSSeedData("89.47.160.243", "89.47.160.243"));
		vSeeds.push_back(CDNSSeedData("192.99.25.243", "192.99.25.243"));
		vSeeds.push_back(CDNSSeedData("89.40.0.219", "89.40.0.219"));
		vSeeds.push_back(CDNSSeedData("81.169.173.24", "81.169.173.24"));
		vSeeds.push_back(CDNSSeedData("80.208.228.127", "80.208.228.127"));
		vSeeds.push_back(CDNSSeedData("80.209.227.184", "80.209.227.184"));
		vSeeds.push_back(CDNSSeedData("89.47.165.5", "89.47.165.5"));
		vSeeds.push_back(CDNSSeedData("45.32.180.99", "45.32.180.99"));
		vSeeds.push_back(CDNSSeedData("95.179.128.210", "95.179.128.210"));
		vSeeds.push_back(CDNSSeedData("18.204.201.10", "18.204.201.10"));
		vSeeds.push_back(CDNSSeedData("89.47.164.84", "89.47.164.84"));
		vSeeds.push_back(CDNSSeedData("144.202.24.155", "144.202.24.155"));
		vSeeds.push_back(CDNSSeedData("95.179.133.196", "95.179.133.196"));
		vSeeds.push_back(CDNSSeedData("89.40.8.68", "89.40.8.68"));
		vSeeds.push_back(CDNSSeedData("199.247.18.190", "199.247.18.190"));
		vSeeds.push_back(CDNSSeedData("176.223.138.170", "176.223.138.170"));
		vSeeds.push_back(CDNSSeedData("199.247.1.107", "199.247.1.107"));
		vSeeds.push_back(CDNSSeedData("176.223.140.93", "176.223.140.93"));
		vSeeds.push_back(CDNSSeedData("140.82.53.76", "140.82.53.76"));
		vSeeds.push_back(CDNSSeedData("80.208.225.198", "80.208.225.198"));
		vSeeds.push_back(CDNSSeedData("207.192.69.4", "207.192.69.4"));
		vSeeds.push_back(CDNSSeedData("47.52.99.4", "47.52.99.4"));
		vSeeds.push_back(CDNSSeedData("207.148.6.231", "207.148.6.231"));
		vSeeds.push_back(CDNSSeedData("89.40.13.111", "89.40.13.111"));
		vSeeds.push_back(CDNSSeedData("192.99.35.221", "192.99.35.221"));
		vSeeds.push_back(CDNSSeedData("89.40.5.231", "89.40.5.231"));
		vSeeds.push_back(CDNSSeedData("80.211.166.52", "80.211.166.52"));
		vSeeds.push_back(CDNSSeedData("136.144.178.254", "136.144.178.254"));
		vSeeds.push_back(CDNSSeedData("45.77.59.206", "45.77.59.206"));
		vSeeds.push_back(CDNSSeedData("178.62.17.37", "178.62.17.37"));
		vSeeds.push_back(CDNSSeedData("178.188.103.66", "178.188.103.66"));
		vSeeds.push_back(CDNSSeedData("176.223.129.237", "176.223.129.237"));
		vSeeds.push_back(CDNSSeedData("159.89.8.137", "159.89.8.137"));
		vSeeds.push_back(CDNSSeedData("45.77.243.93", "45.77.243.93"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("89.47.167.96", "89.47.167.96"));
		vSeeds.push_back(CDNSSeedData("176.223.132.25", "176.223.132.25"));
		vSeeds.push_back(CDNSSeedData("51.15.45.154", "51.15.45.154"));
		vSeeds.push_back(CDNSSeedData("85.88.29.175", "85.88.29.175"));
		vSeeds.push_back(CDNSSeedData("207.148.89.247", "207.148.89.247"));
		vSeeds.push_back(CDNSSeedData("185.204.2.7", "185.204.2.7"));
		vSeeds.push_back(CDNSSeedData("176.223.139.209", "176.223.139.209"));
		vSeeds.push_back(CDNSSeedData("80.209.235.252", "80.209.235.252"));
		vSeeds.push_back(CDNSSeedData("140.82.52.148", "140.82.52.148"));
		vSeeds.push_back(CDNSSeedData("80.240.30.87", "80.240.30.87"));
		vSeeds.push_back(CDNSSeedData("51.15.135.3", "51.15.135.3"));
		vSeeds.push_back(CDNSSeedData("176.223.138.99", "176.223.138.99"));
		vSeeds.push_back(CDNSSeedData("45.32.213.209", "45.32.213.209"));
		vSeeds.push_back(CDNSSeedData("195.181.241.121", "195.181.241.121"));
		vSeeds.push_back(CDNSSeedData("195.181.244.68", "195.181.244.68"));
		vSeeds.push_back(CDNSSeedData("217.69.2.18", "217.69.2.18"));
		vSeeds.push_back(CDNSSeedData("95.179.134.123", "95.179.134.123"));
		vSeeds.push_back(CDNSSeedData("195.181.243.75", "195.181.243.75"));
		vSeeds.push_back(CDNSSeedData("176.223.132.126", "176.223.132.126"));
		vSeeds.push_back(CDNSSeedData("45.76.228.95", "45.76.228.95"));
		vSeeds.push_back(CDNSSeedData("80.211.150.157", "80.211.150.157"));
		vSeeds.push_back(CDNSSeedData("45.76.202.196", "45.76.202.196"));
		vSeeds.push_back(CDNSSeedData("45.32.61.144", "45.32.61.144"));
		vSeeds.push_back(CDNSSeedData("149.28.163.91", "149.28.163.91"));
		vSeeds.push_back(CDNSSeedData("89.40.7.23", "89.40.7.23"));
		vSeeds.push_back(CDNSSeedData("195.181.244.108", "195.181.244.108"));
		vSeeds.push_back(CDNSSeedData("62.77.152.3", "62.77.152.3"));
		vSeeds.push_back(CDNSSeedData("198.13.50.198", "198.13.50.198"));
		vSeeds.push_back(CDNSSeedData("89.40.15.88", "89.40.15.88"));
		vSeeds.push_back(CDNSSeedData("35.229.225.225", "35.229.225.225"));
		vSeeds.push_back(CDNSSeedData("80.209.231.105", "80.209.231.105"));
		vSeeds.push_back(CDNSSeedData("47.92.86.12", "47.92.86.12"));
		vSeeds.push_back(CDNSSeedData("89.40.4.124", "89.40.4.124"));
		vSeeds.push_back(CDNSSeedData("89.40.1.53", "89.40.1.53"));
		vSeeds.push_back(CDNSSeedData("178.128.181.128", "178.128.181.128"));
		vSeeds.push_back(CDNSSeedData("63.211.111.70", "63.211.111.70"));
		vSeeds.push_back(CDNSSeedData("163.172.154.46", "163.172.154.46"));
		vSeeds.push_back(CDNSSeedData("45.77.59.163", "45.77.59.163"));
		vSeeds.push_back(CDNSSeedData("80.208.225.167", "80.208.225.167"));
		vSeeds.push_back(CDNSSeedData("207.148.3.118", "207.148.3.118"));
		vSeeds.push_back(CDNSSeedData("89.40.2.235", "89.40.2.235"));
		vSeeds.push_back(CDNSSeedData("47.75.191.91", "47.75.191.91"));
		vSeeds.push_back(CDNSSeedData("89.47.162.197", "89.47.162.197"));
		vSeeds.push_back(CDNSSeedData("89.47.163.128", "89.47.163.128"));
		vSeeds.push_back(CDNSSeedData("45.32.200.90", "45.32.200.90"));
		vSeeds.push_back(CDNSSeedData("67.205.171.86", "67.205.171.86"));
		vSeeds.push_back(CDNSSeedData("138.201.152.35", "138.201.152.35"));
		vSeeds.push_back(CDNSSeedData("89.40.13.73", "89.40.13.73"));
		vSeeds.push_back(CDNSSeedData("89.40.2.129", "89.40.2.129"));
		vSeeds.push_back(CDNSSeedData("198.13.58.197", "198.13.58.197"));
		vSeeds.push_back(CDNSSeedData("47.52.250.198", "47.52.250.198"));
		vSeeds.push_back(CDNSSeedData("217.69.1.60", "217.69.1.60"));
		vSeeds.push_back(CDNSSeedData("209.250.249.126", "209.250.249.126"));
		vSeeds.push_back(CDNSSeedData("144.202.3.176", "144.202.3.176"));
		vSeeds.push_back(CDNSSeedData("194.135.91.157", "194.135.91.157"));
		vSeeds.push_back(CDNSSeedData("80.209.231.167", "80.209.231.167"));
		vSeeds.push_back(CDNSSeedData("5.45.106.144", "5.45.106.144"));
		vSeeds.push_back(CDNSSeedData("45.76.236.7", "45.76.236.7"));
		vSeeds.push_back(CDNSSeedData("80.209.237.0", "80.209.237.0"));
		vSeeds.push_back(CDNSSeedData("66.42.71.125", "66.42.71.125"));
		vSeeds.push_back(CDNSSeedData("89.40.6.252", "89.40.6.252"));
		vSeeds.push_back(CDNSSeedData("176.223.135.150", "176.223.135.150"));
		vSeeds.push_back(CDNSSeedData("62.77.156.225", "62.77.156.225"));
		vSeeds.push_back(CDNSSeedData("80.209.226.77", "80.209.226.77"));
		vSeeds.push_back(CDNSSeedData("103.72.165.232", "103.72.165.232"));
		vSeeds.push_back(CDNSSeedData("80.240.27.213", "80.240.27.213"));
		vSeeds.push_back(CDNSSeedData("188.68.46.253", "188.68.46.253"));
		vSeeds.push_back(CDNSSeedData("80.240.22.5", "80.240.22.5"));
		vSeeds.push_back(CDNSSeedData("167.99.137.59", "167.99.137.59"));
		vSeeds.push_back(CDNSSeedData("45.76.87.231", "45.76.87.231"));
		vSeeds.push_back(CDNSSeedData("62.77.153.158", "62.77.153.158"));
		vSeeds.push_back(CDNSSeedData("185.81.166.24", "185.81.166.24"));
		vSeeds.push_back(CDNSSeedData("80.209.231.17", "80.209.231.17"));
		vSeeds.push_back(CDNSSeedData("45.77.191.239", "45.77.191.239"));
		vSeeds.push_back(CDNSSeedData("144.202.17.45", "144.202.17.45"));
		vSeeds.push_back(CDNSSeedData("104.238.165.239", "104.238.165.239"));
		vSeeds.push_back(CDNSSeedData("47.254.27.5", "47.254.27.5"));
		vSeeds.push_back(CDNSSeedData("119.3.2.189", "119.3.2.189"));
		vSeeds.push_back(CDNSSeedData("89.47.162.173", "89.47.162.173"));
		vSeeds.push_back(CDNSSeedData("80.209.239.0", "80.209.239.0"));
		vSeeds.push_back(CDNSSeedData("45.32.237.234", "45.32.237.234"));
		vSeeds.push_back(CDNSSeedData("149.28.226.186", "149.28.226.186"));
		vSeeds.push_back(CDNSSeedData("47.52.79.0", "47.52.79.0"));
		vSeeds.push_back(CDNSSeedData("107.191.46.114", "107.191.46.114"));
		vSeeds.push_back(CDNSSeedData("45.32.99.232", "45.32.99.232"));
		vSeeds.push_back(CDNSSeedData("62.77.152.4", "62.77.152.4"));
		vSeeds.push_back(CDNSSeedData("198.57.27.227", "198.57.27.227"));
		vSeeds.push_back(CDNSSeedData("144.202.4.77", "144.202.4.77"));
		vSeeds.push_back(CDNSSeedData("89.47.162.191", "89.47.162.191"));
		vSeeds.push_back(CDNSSeedData("209.250.238.78", "209.250.238.78"));
		vSeeds.push_back(CDNSSeedData("195.54.162.231", "195.54.162.231"));
		vSeeds.push_back(CDNSSeedData("45.77.59.128", "45.77.59.128"));
		vSeeds.push_back(CDNSSeedData("188.68.55.90", "188.68.55.90"));
		vSeeds.push_back(CDNSSeedData("176.223.129.79", "176.223.129.79"));
		vSeeds.push_back(CDNSSeedData("195.181.246.72", "195.181.246.72"));
		vSeeds.push_back(CDNSSeedData("202.182.119.87", "202.182.119.87"));
		vSeeds.push_back(CDNSSeedData("144.202.76.194", "144.202.76.194"));
		vSeeds.push_back(CDNSSeedData("80.211.178.219", "80.211.178.219"));
		vSeeds.push_back(CDNSSeedData("45.32.88.151", "45.32.88.151"));
		vSeeds.push_back(CDNSSeedData("80.209.236.84", "80.209.236.84"));
		vSeeds.push_back(CDNSSeedData("176.223.138.24", "176.223.138.24"));
		vSeeds.push_back(CDNSSeedData("212.47.249.238", "212.47.249.238"));
		vSeeds.push_back(CDNSSeedData("188.166.41.208", "188.166.41.208"));
		vSeeds.push_back(CDNSSeedData("149.28.36.7", "149.28.36.7"));
		vSeeds.push_back(CDNSSeedData("192.3.236.13", "192.3.236.13"));
		vSeeds.push_back(CDNSSeedData("212.24.106.167", "212.24.106.167"));
		vSeeds.push_back(CDNSSeedData("45.63.85.230", "45.63.85.230"));
		vSeeds.push_back(CDNSSeedData("173.249.56.205", "173.249.56.205"));
		vSeeds.push_back(CDNSSeedData("176.223.131.181", "176.223.131.181"));
		vSeeds.push_back(CDNSSeedData("194.28.87.200", "194.28.87.200"));
		vSeeds.push_back(CDNSSeedData("62.77.157.182", "62.77.157.182"));
		vSeeds.push_back(CDNSSeedData("149.28.166.110", "149.28.166.110"));
		vSeeds.push_back(CDNSSeedData("62.77.157.108", "62.77.157.108"));
		vSeeds.push_back(CDNSSeedData("45.77.200.205", "45.77.200.205"));
		vSeeds.push_back(CDNSSeedData("62.77.158.202", "62.77.158.202"));
		vSeeds.push_back(CDNSSeedData("59.42.88.32", "59.42.88.32"));
		vSeeds.push_back(CDNSSeedData("89.40.12.61", "89.40.12.61"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("89.40.4.112", "89.40.4.112"));
		vSeeds.push_back(CDNSSeedData("140.82.39.193", "140.82.39.193"));
		vSeeds.push_back(CDNSSeedData("176.223.131.241", "176.223.131.241"));
		vSeeds.push_back(CDNSSeedData("51.15.212.135", "51.15.212.135"));
		vSeeds.push_back(CDNSSeedData("144.202.22.225", "144.202.22.225"));
		vSeeds.push_back(CDNSSeedData("66.42.66.224", "66.42.66.224"));
		vSeeds.push_back(CDNSSeedData("62.77.153.239", "62.77.153.239"));
		vSeeds.push_back(CDNSSeedData("94.176.234.47", "94.176.234.47"));
		vSeeds.push_back(CDNSSeedData("47.92.160.138", "47.92.160.138"));
		vSeeds.push_back(CDNSSeedData("107.172.252.238", "107.172.252.238"));
		vSeeds.push_back(CDNSSeedData("45.76.228.100", "45.76.228.100"));
		vSeeds.push_back(CDNSSeedData("199.247.10.171", "199.247.10.171"));
		vSeeds.push_back(CDNSSeedData("176.223.130.157", "176.223.130.157"));
		vSeeds.push_back(CDNSSeedData("89.47.165.1", "89.47.165.1"));
		vSeeds.push_back(CDNSSeedData("199.247.11.52", "199.247.11.52"));
		vSeeds.push_back(CDNSSeedData("176.223.138.181", "176.223.138.181"));
		vSeeds.push_back(CDNSSeedData("94.176.236.70", "94.176.236.70"));
		vSeeds.push_back(CDNSSeedData("89.40.2.102", "89.40.2.102"));
		vSeeds.push_back(CDNSSeedData("212.24.109.240", "212.24.109.240"));
		vSeeds.push_back(CDNSSeedData("159.65.204.2", "159.65.204.2"));
		vSeeds.push_back(CDNSSeedData("45.32.162.58", "45.32.162.58"));
		vSeeds.push_back(CDNSSeedData("217.69.8.247", "217.69.8.247"));
		vSeeds.push_back(CDNSSeedData("80.211.216.151", "80.211.216.151"));
		vSeeds.push_back(CDNSSeedData("178.62.31.191", "178.62.31.191"));
		vSeeds.push_back(CDNSSeedData("140.82.32.213", "140.82.32.213"));
		vSeeds.push_back(CDNSSeedData("89.40.6.135", "89.40.6.135"));
		vSeeds.push_back(CDNSSeedData("47.52.192.27", "47.52.192.27"));
		vSeeds.push_back(CDNSSeedData("128.199.62.237", "128.199.62.237"));
		vSeeds.push_back(CDNSSeedData("89.40.6.34", "89.40.6.34"));
		vSeeds.push_back(CDNSSeedData("94.176.235.107", "94.176.235.107"));
		vSeeds.push_back(CDNSSeedData("176.223.131.116", "176.223.131.116"));
		vSeeds.push_back(CDNSSeedData("195.201.45.178", "195.201.45.178"));
		vSeeds.push_back(CDNSSeedData("62.77.157.53", "62.77.157.53"));
		vSeeds.push_back(CDNSSeedData("45.63.100.58", "45.63.100.58"));
		vSeeds.push_back(CDNSSeedData("159.65.65.235", "159.65.65.235"));
		vSeeds.push_back(CDNSSeedData("124.135.51.50", "124.135.51.50"));
		vSeeds.push_back(CDNSSeedData("52.90.18.102", "52.90.18.102"));
		vSeeds.push_back(CDNSSeedData("140.82.29.37", "140.82.29.37"));
		vSeeds.push_back(CDNSSeedData("45.32.114.185", "45.32.114.185"));
		vSeeds.push_back(CDNSSeedData("45.32.185.146", "45.32.185.146"));
		vSeeds.push_back(CDNSSeedData("35.229.222.154", "35.229.222.154"));
		vSeeds.push_back(CDNSSeedData("45.77.229.208", "45.77.229.208"));
		vSeeds.push_back(CDNSSeedData("31.214.144.41", "31.214.144.41"));
		vSeeds.push_back(CDNSSeedData("222.191.227.123", "222.191.227.123"));
		vSeeds.push_back(CDNSSeedData("80.209.239.35", "80.209.239.35"));
		vSeeds.push_back(CDNSSeedData("95.179.136.184", "95.179.136.184"));
		vSeeds.push_back(CDNSSeedData("185.233.106.67", "185.233.106.67"));
		vSeeds.push_back(CDNSSeedData("185.92.221.20", "185.92.221.20"));
		vSeeds.push_back(CDNSSeedData("89.47.163.227", "89.47.163.227"));
		vSeeds.push_back(CDNSSeedData("212.24.98.180", "212.24.98.180"));
		vSeeds.push_back(CDNSSeedData("188.68.45.140", "188.68.45.140"));
		vSeeds.push_back(CDNSSeedData("89.40.2.99", "89.40.2.99"));
		vSeeds.push_back(CDNSSeedData("202.182.108.194", "202.182.108.194"));
		vSeeds.push_back(CDNSSeedData("80.240.31.42", "80.240.31.42"));
		vSeeds.push_back(CDNSSeedData("45.76.21.181", "45.76.21.181"));
		vSeeds.push_back(CDNSSeedData("95.179.159.70", "95.179.159.70"));
		vSeeds.push_back(CDNSSeedData("89.47.164.82", "89.47.164.82"));
		vSeeds.push_back(CDNSSeedData("206.189.82.41", "206.189.82.41"));
		vSeeds.push_back(CDNSSeedData("194.182.67.26", "194.182.67.26"));
		vSeeds.push_back(CDNSSeedData("80.209.232.12", "80.209.232.12"));
		vSeeds.push_back(CDNSSeedData("144.202.0.145", "144.202.0.145"));
		vSeeds.push_back(CDNSSeedData("195.181.241.106", "195.181.241.106"));
		vSeeds.push_back(CDNSSeedData("212.24.105.68", "212.24.105.68"));
		vSeeds.push_back(CDNSSeedData("149.28.96.152", "149.28.96.152"));
		vSeeds.push_back(CDNSSeedData("45.76.230.95", "45.76.230.95"));
		vSeeds.push_back(CDNSSeedData("45.77.0.17", "45.77.0.17"));
		vSeeds.push_back(CDNSSeedData("80.209.232.10", "80.209.232.10"));
		vSeeds.push_back(CDNSSeedData("194.67.194.116", "194.67.194.116"));
		vSeeds.push_back(CDNSSeedData("62.77.155.87", "62.77.155.87"));
		vSeeds.push_back(CDNSSeedData("45.77.73.37", "45.77.73.37"));
		vSeeds.push_back(CDNSSeedData("89.40.8.73", "89.40.8.73"));
		vSeeds.push_back(CDNSSeedData("89.46.73.221", "89.46.73.221"));
		vSeeds.push_back(CDNSSeedData("94.176.237.180", "94.176.237.180"));
		vSeeds.push_back(CDNSSeedData("62.77.158.31", "62.77.158.31"));
		vSeeds.push_back(CDNSSeedData("173.44.208.47", "173.44.208.47"));
		vSeeds.push_back(CDNSSeedData("144.202.17.57", "144.202.17.57"));
		vSeeds.push_back(CDNSSeedData("198.13.34.166", "198.13.34.166"));
		vSeeds.push_back(CDNSSeedData("95.216.141.198", "95.216.141.198"));
		vSeeds.push_back(CDNSSeedData("209.250.237.82", "209.250.237.82"));
		vSeeds.push_back(CDNSSeedData("80.208.226.223", "80.208.226.223"));
		vSeeds.push_back(CDNSSeedData("47.92.32.113", "47.92.32.113"));
		vSeeds.push_back(CDNSSeedData("45.32.235.205", "45.32.235.205"));
		vSeeds.push_back(CDNSSeedData("45.77.225.182", "45.77.225.182"));
		vSeeds.push_back(CDNSSeedData("96.72.26.75", "96.72.26.75"));
		vSeeds.push_back(CDNSSeedData("80.240.19.28", "80.240.19.28"));
		vSeeds.push_back(CDNSSeedData("91.235.129.245", "91.235.129.245"));
		vSeeds.push_back(CDNSSeedData("47.92.29.81", "47.92.29.81"));
		vSeeds.push_back(CDNSSeedData("45.32.148.192", "45.32.148.192"));
		vSeeds.push_back(CDNSSeedData("45.77.0.207", "45.77.0.207"));
		vSeeds.push_back(CDNSSeedData("209.250.251.239", "209.250.251.239"));
		vSeeds.push_back(CDNSSeedData("45.63.93.86", "45.63.93.86"));
		vSeeds.push_back(CDNSSeedData("80.209.237.103", "80.209.237.103"));
		vSeeds.push_back(CDNSSeedData("89.47.162.171", "89.47.162.171"));
		vSeeds.push_back(CDNSSeedData("89.40.10.114", "89.40.10.114"));
		vSeeds.push_back(CDNSSeedData("45.76.206.181", "45.76.206.181"));
		vSeeds.push_back(CDNSSeedData("172.104.18.182", "172.104.18.182"));
		vSeeds.push_back(CDNSSeedData("89.40.5.47", "89.40.5.47"));
		vSeeds.push_back(CDNSSeedData("173.44.208.44", "173.44.208.44"));
		vSeeds.push_back(CDNSSeedData("80.209.238.208", "80.209.238.208"));
		vSeeds.push_back(CDNSSeedData("54.226.207.127", "54.226.207.127"));
		vSeeds.push_back(CDNSSeedData("62.77.156.101", "62.77.156.101"));
		vSeeds.push_back(CDNSSeedData("89.40.12.105", "89.40.12.105"));
		vSeeds.push_back(CDNSSeedData("104.238.176.7", "104.238.176.7"));
		vSeeds.push_back(CDNSSeedData("85.214.56.229", "85.214.56.229"));
		vSeeds.push_back(CDNSSeedData("51.15.73.124", "51.15.73.124"));
		vSeeds.push_back(CDNSSeedData("62.77.156.222", "62.77.156.222"));
		vSeeds.push_back(CDNSSeedData("45.77.214.34", "45.77.214.34"));
		vSeeds.push_back(CDNSSeedData("47.52.138.227", "47.52.138.227"));
		vSeeds.push_back(CDNSSeedData("45.76.111.94", "45.76.111.94"));
		vSeeds.push_back(CDNSSeedData("199.247.10.11", "199.247.10.11"));
		vSeeds.push_back(CDNSSeedData("139.59.91.86", "139.59.91.86"));
		vSeeds.push_back(CDNSSeedData("45.76.151.23", "45.76.151.23"));
		vSeeds.push_back(CDNSSeedData("176.223.130.218", "176.223.130.218"));
		vSeeds.push_back(CDNSSeedData("31.131.17.95", "31.131.17.95"));
		vSeeds.push_back(CDNSSeedData("89.40.15.77", "89.40.15.77"));
		vSeeds.push_back(CDNSSeedData("217.69.2.90", "217.69.2.90"));
		vSeeds.push_back(CDNSSeedData("54.67.115.113", "54.67.115.113"));
		vSeeds.push_back(CDNSSeedData("95.179.133.129", "95.179.133.129"));
		vSeeds.push_back(CDNSSeedData("89.47.166.239", "89.47.166.239"));
		vSeeds.push_back(CDNSSeedData("80.240.23.61", "80.240.23.61"));
		vSeeds.push_back(CDNSSeedData("209.250.230.75", "209.250.230.75"));
		vSeeds.push_back(CDNSSeedData("89.40.7.24", "89.40.7.24"));
		vSeeds.push_back(CDNSSeedData("89.40.10.115", "89.40.10.115"));
		vSeeds.push_back(CDNSSeedData("94.176.239.228", "94.176.239.228"));
		vSeeds.push_back(CDNSSeedData("80.209.236.115", "80.209.236.115"));
		vSeeds.push_back(CDNSSeedData("89.40.7.21", "89.40.7.21"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("149.28.113.206", "149.28.113.206"));
		vSeeds.push_back(CDNSSeedData("45.32.247.149", "45.32.247.149"));
		vSeeds.push_back(CDNSSeedData("89.47.167.1", "89.47.167.1"));
		vSeeds.push_back(CDNSSeedData("217.69.7.247", "217.69.7.247"));
		vSeeds.push_back(CDNSSeedData("176.223.132.131", "176.223.132.131"));
		vSeeds.push_back(CDNSSeedData("35.193.194.35", "35.193.194.35"));
		vSeeds.push_back(CDNSSeedData("45.76.18.145", "45.76.18.145"));
		vSeeds.push_back(CDNSSeedData("51.15.86.24", "51.15.86.24"));
		vSeeds.push_back(CDNSSeedData("176.223.134.176", "176.223.134.176"));
		vSeeds.push_back(CDNSSeedData("80.208.228.196", "80.208.228.196"));
		vSeeds.push_back(CDNSSeedData("86.121.208.47", "86.121.208.47"));
		vSeeds.push_back(CDNSSeedData("149.28.13.252", "149.28.13.252"));
		vSeeds.push_back(CDNSSeedData("80.211.202.156", "80.211.202.156"));
		vSeeds.push_back(CDNSSeedData("144.202.69.186", "144.202.69.186"));
		vSeeds.push_back(CDNSSeedData("207.246.123.142", "207.246.123.142"));
		vSeeds.push_back(CDNSSeedData("80.211.207.80", "80.211.207.80"));
		vSeeds.push_back(CDNSSeedData("108.61.221.163", "108.61.221.163"));
		vSeeds.push_back(CDNSSeedData("47.92.32.105", "47.92.32.105"));
		vSeeds.push_back(CDNSSeedData("107.191.47.66", "107.191.47.66"));
		vSeeds.push_back(CDNSSeedData("212.24.108.64", "212.24.108.64"));
		vSeeds.push_back(CDNSSeedData("155.94.226.42", "155.94.226.42"));
		vSeeds.push_back(CDNSSeedData("89.47.166.67", "89.47.166.67"));
		vSeeds.push_back(CDNSSeedData("80.209.229.97", "80.209.229.97"));
		vSeeds.push_back(CDNSSeedData("95.216.142.83", "95.216.142.83"));
		vSeeds.push_back(CDNSSeedData("45.76.56.167", "45.76.56.167"));
		vSeeds.push_back(CDNSSeedData("89.40.2.233", "89.40.2.233"));
		vSeeds.push_back(CDNSSeedData("62.77.159.141", "62.77.159.141"));
		vSeeds.push_back(CDNSSeedData("45.77.24.225", "45.77.24.225"));
		vSeeds.push_back(CDNSSeedData("47.92.117.194", "47.92.117.194"));
		vSeeds.push_back(CDNSSeedData("108.61.252.235", "108.61.252.235"));
		vSeeds.push_back(CDNSSeedData("176.223.134.172", "176.223.134.172"));
		vSeeds.push_back(CDNSSeedData("95.179.167.71", "95.179.167.71"));
		vSeeds.push_back(CDNSSeedData("89.40.11.240", "89.40.11.240"));
		vSeeds.push_back(CDNSSeedData("80.208.230.116", "80.208.230.116"));
		vSeeds.push_back(CDNSSeedData("80.209.231.97", "80.209.231.97"));
		vSeeds.push_back(CDNSSeedData("163.172.168.140", "163.172.168.140"));
		vSeeds.push_back(CDNSSeedData("89.47.161.180", "89.47.161.180"));
		vSeeds.push_back(CDNSSeedData("80.211.144.241", "80.211.144.241"));
		vSeeds.push_back(CDNSSeedData("144.202.101.133", "144.202.101.133"));
		vSeeds.push_back(CDNSSeedData("140.82.24.69", "140.82.24.69"));
		vSeeds.push_back(CDNSSeedData("80.211.165.96", "80.211.165.96"));
		vSeeds.push_back(CDNSSeedData("89.47.160.248", "89.47.160.248"));
		vSeeds.push_back(CDNSSeedData("212.47.228.99", "212.47.228.99"));
		vSeeds.push_back(CDNSSeedData("45.77.41.111", "45.77.41.111"));
		vSeeds.push_back(CDNSSeedData("193.124.57.56", "193.124.57.56"));
		vSeeds.push_back(CDNSSeedData("95.179.129.44", "95.179.129.44"));
		vSeeds.push_back(CDNSSeedData("172.104.35.224", "172.104.35.224"));
		vSeeds.push_back(CDNSSeedData("45.32.21.8", "45.32.21.8"));
		vSeeds.push_back(CDNSSeedData("176.223.130.213", "176.223.130.213"));
		vSeeds.push_back(CDNSSeedData("13.90.229.232", "13.90.229.232"));
		vSeeds.push_back(CDNSSeedData("194.135.90.237", "194.135.90.237"));
		vSeeds.push_back(CDNSSeedData("89.40.6.96", "89.40.6.96"));
		vSeeds.push_back(CDNSSeedData("222.191.227.125", "222.191.227.125"));
		vSeeds.push_back(CDNSSeedData("199.247.25.139", "199.247.25.139"));
		vSeeds.push_back(CDNSSeedData("144.202.102.192", "144.202.102.192"));
		vSeeds.push_back(CDNSSeedData("88.99.15.196", "88.99.15.196"));
		vSeeds.push_back(CDNSSeedData("159.69.12.231", "159.69.12.231"));
		vSeeds.push_back(CDNSSeedData("45.32.220.133", "45.32.220.133"));
		vSeeds.push_back(CDNSSeedData("108.61.174.28", "108.61.174.28"));
		vSeeds.push_back(CDNSSeedData("80.208.224.88", "80.208.224.88"));
		vSeeds.push_back(CDNSSeedData("199.247.17.0", "199.247.17.0"));
		vSeeds.push_back(CDNSSeedData("80.209.227.56", "80.209.227.56"));
		vSeeds.push_back(CDNSSeedData("185.92.223.191", "185.92.223.191"));
		vSeeds.push_back(CDNSSeedData("140.82.55.192", "140.82.55.192"));
		vSeeds.push_back(CDNSSeedData("89.40.2.187", "89.40.2.187"));
		vSeeds.push_back(CDNSSeedData("34.245.170.215", "34.245.170.215"));
		vSeeds.push_back(CDNSSeedData("45.76.23.127", "45.76.23.127"));
		vSeeds.push_back(CDNSSeedData("62.77.158.107", "62.77.158.107"));
		vSeeds.push_back(CDNSSeedData("80.211.172.154", "80.211.172.154"));
		vSeeds.push_back(CDNSSeedData("95.179.137.155", "95.179.137.155"));
		vSeeds.push_back(CDNSSeedData("45.76.152.151", "45.76.152.151"));
		vSeeds.push_back(CDNSSeedData("140.82.35.26", "140.82.35.26"));
		vSeeds.push_back(CDNSSeedData("45.32.42.43", "45.32.42.43"));
		vSeeds.push_back(CDNSSeedData("73.76.16.176", "73.76.16.176"));
		vSeeds.push_back(CDNSSeedData("188.166.32.109", "188.166.32.109"));
		vSeeds.push_back(CDNSSeedData("149.28.204.90", "149.28.204.90"));
		vSeeds.push_back(CDNSSeedData("62.77.159.57", "62.77.159.57"));
		vSeeds.push_back(CDNSSeedData("78.46.209.248", "78.46.209.248"));
		vSeeds.push_back(CDNSSeedData("47.92.166.134", "47.92.166.134"));
		vSeeds.push_back(CDNSSeedData("62.77.153.112", "62.77.153.112"));
		vSeeds.push_back(CDNSSeedData("207.148.83.95", "207.148.83.95"));
		vSeeds.push_back(CDNSSeedData("207.148.81.191", "207.148.81.191"));
		vSeeds.push_back(CDNSSeedData("217.163.28.65", "217.163.28.65"));
		vSeeds.push_back(CDNSSeedData("45.63.107.221", "45.63.107.221"));
		vSeeds.push_back(CDNSSeedData("89.47.166.70", "89.47.166.70"));
		vSeeds.push_back(CDNSSeedData("80.209.227.123", "80.209.227.123"));
		vSeeds.push_back(CDNSSeedData("149.28.34.117", "149.28.34.117"));
		vSeeds.push_back(CDNSSeedData("176.223.139.210", "176.223.139.210"));
		vSeeds.push_back(CDNSSeedData("45.77.53.97", "45.77.53.97"));
		vSeeds.push_back(CDNSSeedData("149.28.137.145", "149.28.137.145"));
		vSeeds.push_back(CDNSSeedData("167.160.84.159", "167.160.84.159"));
		vSeeds.push_back(CDNSSeedData("89.40.13.71", "89.40.13.71"));
		vSeeds.push_back(CDNSSeedData("176.223.130.126", "176.223.130.126"));
		vSeeds.push_back(CDNSSeedData("62.77.152.5", "62.77.152.5"));
		vSeeds.push_back(CDNSSeedData("45.77.63.5", "45.77.63.5"));
		vSeeds.push_back(CDNSSeedData("89.47.167.200", "89.47.167.200"));
		vSeeds.push_back(CDNSSeedData("140.82.55.171", "140.82.55.171"));
		vSeeds.push_back(CDNSSeedData("185.233.106.217", "185.233.106.217"));
		vSeeds.push_back(CDNSSeedData("207.246.103.237", "207.246.103.237"));
		vSeeds.push_back(CDNSSeedData("89.47.167.9", "89.47.167.9"));
		vSeeds.push_back(CDNSSeedData("212.24.107.184", "212.24.107.184"));
		vSeeds.push_back(CDNSSeedData("199.247.18.205", "199.247.18.205"));
		vSeeds.push_back(CDNSSeedData("66.42.48.236", "66.42.48.236"));
		vSeeds.push_back(CDNSSeedData("104.196.0.22", "104.196.0.22"));
		vSeeds.push_back(CDNSSeedData("199.59.83.137", "199.59.83.137"));
		vSeeds.push_back(CDNSSeedData("89.47.164.159", "89.47.164.159"));
		vSeeds.push_back(CDNSSeedData("109.235.70.102", "109.235.70.102"));
		vSeeds.push_back(CDNSSeedData("45.77.205.149", "45.77.205.149"));
		vSeeds.push_back(CDNSSeedData("51.15.198.176", "51.15.198.176"));
		vSeeds.push_back(CDNSSeedData("144.202.21.244", "144.202.21.244"));
		vSeeds.push_back(CDNSSeedData("62.77.159.6", "62.77.159.6"));
		vSeeds.push_back(CDNSSeedData("138.68.83.83", "138.68.83.83"));
		vSeeds.push_back(CDNSSeedData("45.77.110.15", "45.77.110.15"));
		vSeeds.push_back(CDNSSeedData("62.77.153.167", "62.77.153.167"));
		vSeeds.push_back(CDNSSeedData("198.58.107.178", "198.58.107.178"));
		vSeeds.push_back(CDNSSeedData("89.40.13.67", "89.40.13.67"));
		vSeeds.push_back(CDNSSeedData("45.76.83.205", "45.76.83.205"));
		vSeeds.push_back(CDNSSeedData("54.36.189.38", "54.36.189.38"));
		vSeeds.push_back(CDNSSeedData("94.16.118.27", "94.16.118.27"));
		vSeeds.push_back(CDNSSeedData("80.208.231.226", "80.208.231.226"));
		vSeeds.push_back(CDNSSeedData("62.77.153.166", "62.77.153.166"));
		vSeeds.push_back(CDNSSeedData("207.148.5.148", "207.148.5.148"));
		vSeeds.push_back(CDNSSeedData("64.154.38.242", "64.154.38.242"));
		vSeeds.push_back(CDNSSeedData("62.77.155.200", "62.77.155.200"));
		vSeeds.push_back(CDNSSeedData("89.47.167.164", "89.47.167.164"));
		vSeeds.push_back(CDNSSeedData("18.219.202.255", "18.219.202.255"));
		vSeeds.push_back(CDNSSeedData("66.228.42.5", "66.228.42.5"));
		vSeeds.push_back(CDNSSeedData("176.223.139.125", "176.223.139.125"));
		vSeeds.push_back(CDNSSeedData("176.223.131.98", "176.223.131.98"));
		vSeeds.push_back(CDNSSeedData("139.162.168.95", "139.162.168.95"));
		vSeeds.push_back(CDNSSeedData("89.47.160.90", "89.47.160.90"));
		vSeeds.push_back(CDNSSeedData("176.223.132.127", "176.223.132.127"));
		vSeeds.push_back(CDNSSeedData("89.40.11.191", "89.40.11.191"));
		vSeeds.push_back(CDNSSeedData("66.42.42.152", "66.42.42.152"));
		vSeeds.push_back(CDNSSeedData("145.239.83.89", "145.239.83.89"));
		vSeeds.push_back(CDNSSeedData("95.179.147.218", "95.179.147.218"));
		vSeeds.push_back(CDNSSeedData("89.40.13.135", "89.40.13.135"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("217.69.4.190", "217.69.4.190"));
		vSeeds.push_back(CDNSSeedData("95.179.151.139", "95.179.151.139"));
		vSeeds.push_back(CDNSSeedData("79.98.24.210", "79.98.24.210"));
		vSeeds.push_back(CDNSSeedData("89.40.2.232", "89.40.2.232"));
		vSeeds.push_back(CDNSSeedData("45.63.117.99", "45.63.117.99"));
		vSeeds.push_back(CDNSSeedData("104.238.147.70", "104.238.147.70"));
		vSeeds.push_back(CDNSSeedData("54.153.4.252", "54.153.4.252"));
		vSeeds.push_back(CDNSSeedData("94.176.232.34", "94.176.232.34"));
		vSeeds.push_back(CDNSSeedData("185.5.52.118", "185.5.52.118"));
		vSeeds.push_back(CDNSSeedData("94.176.232.13", "94.176.232.13"));
		vSeeds.push_back(CDNSSeedData("176.223.139.8", "176.223.139.8"));
		vSeeds.push_back(CDNSSeedData("185.80.128.144", "185.80.128.144"));
		vSeeds.push_back(CDNSSeedData("176.223.142.29", "176.223.142.29"));
		vSeeds.push_back(CDNSSeedData("94.16.118.146", "94.16.118.146"));
		vSeeds.push_back(CDNSSeedData("89.40.5.54", "89.40.5.54"));
		vSeeds.push_back(CDNSSeedData("207.148.13.187", "207.148.13.187"));
		vSeeds.push_back(CDNSSeedData("89.40.10.109", "89.40.10.109"));
		vSeeds.push_back(CDNSSeedData("89.40.2.182", "89.40.2.182"));
		vSeeds.push_back(CDNSSeedData("185.69.53.88", "185.69.53.88"));
		vSeeds.push_back(CDNSSeedData("176.223.139.126", "176.223.139.126"));
		vSeeds.push_back(CDNSSeedData("144.202.43.111", "144.202.43.111"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("144.202.91.237", "144.202.91.237"));
		vSeeds.push_back(CDNSSeedData("62.77.153.253", "62.77.153.253"));
		vSeeds.push_back(CDNSSeedData("80.209.236.51", "80.209.236.51"));
		vSeeds.push_back(CDNSSeedData("89.40.6.212", "89.40.6.212"));
		vSeeds.push_back(CDNSSeedData("176.223.139.124", "176.223.139.124"));
		vSeeds.push_back(CDNSSeedData("69.165.192.43", "69.165.192.43"));
		vSeeds.push_back(CDNSSeedData("104.238.170.152", "104.238.170.152"));
		vSeeds.push_back(CDNSSeedData("212.47.246.129", "212.47.246.129"));
		vSeeds.push_back(CDNSSeedData("89.40.8.17", "89.40.8.17"));
		vSeeds.push_back(CDNSSeedData("144.202.91.163", "144.202.91.163"));
		vSeeds.push_back(CDNSSeedData("45.76.176.227", "45.76.176.227"));
		vSeeds.push_back(CDNSSeedData("195.201.139.42", "195.201.139.42"));
		vSeeds.push_back(CDNSSeedData("45.76.24.80", "45.76.24.80"));
		vSeeds.push_back(CDNSSeedData("52.151.11.125", "52.151.11.125"));
		vSeeds.push_back(CDNSSeedData("80.211.178.127", "80.211.178.127"));
		vSeeds.push_back(CDNSSeedData("176.223.140.2", "176.223.140.2"));
		vSeeds.push_back(CDNSSeedData("206.189.38.60", "206.189.38.60"));
		vSeeds.push_back(CDNSSeedData("207.246.127.135", "207.246.127.135"));
		vSeeds.push_back(CDNSSeedData("62.77.153.27", "62.77.153.27"));
		vSeeds.push_back(CDNSSeedData("89.40.12.121", "89.40.12.121"));
		vSeeds.push_back(CDNSSeedData("142.44.206.229", "142.44.206.229"));
		vSeeds.push_back(CDNSSeedData("176.223.134.74", "176.223.134.74"));
		vSeeds.push_back(CDNSSeedData("80.208.229.210", "80.208.229.210"));
		vSeeds.push_back(CDNSSeedData("89.40.2.230", "89.40.2.230"));
		vSeeds.push_back(CDNSSeedData("89.40.8.20", "89.40.8.20"));
		vSeeds.push_back(CDNSSeedData("176.223.137.138", "176.223.137.138"));
		vSeeds.push_back(CDNSSeedData("80.208.227.136", "80.208.227.136"));
		vSeeds.push_back(CDNSSeedData("80.211.11.104", "80.211.11.104"));
		vSeeds.push_back(CDNSSeedData("207.148.9.101", "207.148.9.101"));
		vSeeds.push_back(CDNSSeedData("88.99.33.209", "88.99.33.209"));
		vSeeds.push_back(CDNSSeedData("176.223.138.168", "176.223.138.168"));
		vSeeds.push_back(CDNSSeedData("45.77.56.234", "45.77.56.234"));
		vSeeds.push_back(CDNSSeedData("47.92.139.179", "47.92.139.179"));
		vSeeds.push_back(CDNSSeedData("89.40.1.86", "89.40.1.86"));
		vSeeds.push_back(CDNSSeedData("107.170.255.216", "107.170.255.216"));
		vSeeds.push_back(CDNSSeedData("89.40.10.62", "89.40.10.62"));
		vSeeds.push_back(CDNSSeedData("176.223.133.7", "176.223.133.7"));
		vSeeds.push_back(CDNSSeedData("144.202.24.218", "144.202.24.218"));
		vSeeds.push_back(CDNSSeedData("209.250.237.77", "209.250.237.77"));
		vSeeds.push_back(CDNSSeedData("45.77.211.106", "45.77.211.106"));
		vSeeds.push_back(CDNSSeedData("80.209.236.249", "80.209.236.249"));
		vSeeds.push_back(CDNSSeedData("62.77.157.58", "62.77.157.58"));
		vSeeds.push_back(CDNSSeedData("62.77.153.113", "62.77.153.113"));
		vSeeds.push_back(CDNSSeedData("80.209.236.102", "80.209.236.102"));
		vSeeds.push_back(CDNSSeedData("34.224.102.78", "34.224.102.78"));
		vSeeds.push_back(CDNSSeedData("35.189.173.72", "35.189.173.72"));
		vSeeds.push_back(CDNSSeedData("212.24.110.33", "212.24.110.33"));
		vSeeds.push_back(CDNSSeedData("45.32.225.221", "45.32.225.221"));
		vSeeds.push_back(CDNSSeedData("89.40.12.54", "89.40.12.54"));
		vSeeds.push_back(CDNSSeedData("95.179.141.65", "95.179.141.65"));
		vSeeds.push_back(CDNSSeedData("149.28.43.27", "149.28.43.27"));
		vSeeds.push_back(CDNSSeedData("89.40.2.222", "89.40.2.222"));
		vSeeds.push_back(CDNSSeedData("45.32.220.42", "45.32.220.42"));
		vSeeds.push_back(CDNSSeedData("45.76.150.203", "45.76.150.203"));
		vSeeds.push_back(CDNSSeedData("89.40.7.18", "89.40.7.18"));
		vSeeds.push_back(CDNSSeedData("89.40.12.35", "89.40.12.35"));
		vSeeds.push_back(CDNSSeedData("144.202.48.239", "144.202.48.239"));
		vSeeds.push_back(CDNSSeedData("62.77.155.45", "62.77.155.45"));
		vSeeds.push_back(CDNSSeedData("62.77.155.48", "62.77.155.48"));
		vSeeds.push_back(CDNSSeedData("45.63.105.210", "45.63.105.210"));
		vSeeds.push_back(CDNSSeedData("159.89.119.82", "159.89.119.82"));
		vSeeds.push_back(CDNSSeedData("209.250.240.19", "209.250.240.19"));
		vSeeds.push_back(CDNSSeedData("207.148.90.33", "207.148.90.33"));
		vSeeds.push_back(CDNSSeedData("35.189.170.4", "35.189.170.4"));
		vSeeds.push_back(CDNSSeedData("94.176.233.28", "94.176.233.28"));
		vSeeds.push_back(CDNSSeedData("89.40.12.145", "89.40.12.145"));
		vSeeds.push_back(CDNSSeedData("31.214.144.239", "31.214.144.239"));
		vSeeds.push_back(CDNSSeedData("139.99.202.39", "139.99.202.39"));
		vSeeds.push_back(CDNSSeedData("108.61.178.46", "108.61.178.46"));
		vSeeds.push_back(CDNSSeedData("176.223.132.132", "176.223.132.132"));
		vSeeds.push_back(CDNSSeedData("45.32.193.236", "45.32.193.236"));
		vSeeds.push_back(CDNSSeedData("89.40.5.38", "89.40.5.38"));
		vSeeds.push_back(CDNSSeedData("80.208.228.187", "80.208.228.187"));
		vSeeds.push_back(CDNSSeedData("144.202.83.85", "144.202.83.85"));
		vSeeds.push_back(CDNSSeedData("75.73.128.164", "75.73.128.164"));
		vSeeds.push_back(CDNSSeedData("176.223.131.168", "176.223.131.168"));
		vSeeds.push_back(CDNSSeedData("45.77.150.54", "45.77.150.54"));
		vSeeds.push_back(CDNSSeedData("176.223.131.193", "176.223.131.193"));
		vSeeds.push_back(CDNSSeedData("113.20.30.180", "113.20.30.180"));
		vSeeds.push_back(CDNSSeedData("45.63.97.191", "45.63.97.191"));
		vSeeds.push_back(CDNSSeedData("89.40.12.104", "89.40.12.104"));
		vSeeds.push_back(CDNSSeedData("45.55.210.13", "45.55.210.13"));
		vSeeds.push_back(CDNSSeedData("89.47.166.166", "89.47.166.166"));
		vSeeds.push_back(CDNSSeedData("108.61.199.181", "108.61.199.181"));
		vSeeds.push_back(CDNSSeedData("45.77.167.16", "45.77.167.16"));
		vSeeds.push_back(CDNSSeedData("80.211.214.55", "80.211.214.55"));
		vSeeds.push_back(CDNSSeedData("47.254.133.231", "47.254.133.231"));
		vSeeds.push_back(CDNSSeedData("89.40.5.50", "89.40.5.50"));
		vSeeds.push_back(CDNSSeedData("209.250.245.34", "209.250.245.34"));
		vSeeds.push_back(CDNSSeedData("62.77.153.29", "62.77.153.29"));
		vSeeds.push_back(CDNSSeedData("89.47.160.108", "89.47.160.108"));
		vSeeds.push_back(CDNSSeedData("45.32.160.214", "45.32.160.214"));
		vSeeds.push_back(CDNSSeedData("207.148.69.175", "207.148.69.175"));
		vSeeds.push_back(CDNSSeedData("89.40.10.110", "89.40.10.110"));
		vSeeds.push_back(CDNSSeedData("45.32.50.55", "45.32.50.55"));
		vSeeds.push_back(CDNSSeedData("195.201.34.154", "195.201.34.154"));
		vSeeds.push_back(CDNSSeedData("89.40.10.126", "89.40.10.126"));
		vSeeds.push_back(CDNSSeedData("47.92.86.21", "47.92.86.21"));
		vSeeds.push_back(CDNSSeedData("93.186.253.182", "93.186.253.182"));
		vSeeds.push_back(CDNSSeedData("89.40.13.113", "89.40.13.113"));
		vSeeds.push_back(CDNSSeedData("139.162.141.129", "139.162.141.129"));
		vSeeds.push_back(CDNSSeedData("89.47.163.142", "89.47.163.142"));
		vSeeds.push_back(CDNSSeedData("89.47.160.75", "89.47.160.75"));
		vSeeds.push_back(CDNSSeedData("80.209.224.239", "80.209.224.239"));
		vSeeds.push_back(CDNSSeedData("89.47.167.162", "89.47.167.162"));
		vSeeds.push_back(CDNSSeedData("149.28.236.250", "149.28.236.250"));
		vSeeds.push_back(CDNSSeedData("45.76.131.129", "45.76.131.129"));
		vSeeds.push_back(CDNSSeedData("51.38.178.86", "51.38.178.86"));
		vSeeds.push_back(CDNSSeedData("80.209.230.130", "80.209.230.130"));
		vSeeds.push_back(CDNSSeedData("173.249.43.72", "173.249.43.72"));
		vSeeds.push_back(CDNSSeedData("45.32.140.75", "45.32.140.75"));
		vSeeds.push_back(CDNSSeedData("107.173.125.204", "107.173.125.204"));
		vSeeds.push_back(CDNSSeedData("149.28.117.233", "149.28.117.233"));
		vSeeds.push_back(CDNSSeedData("89.40.12.141", "89.40.12.141"));
		vSeeds.push_back(CDNSSeedData("80.209.224.146", "80.209.224.146"));
		vSeeds.push_back(CDNSSeedData("89.40.6.139", "89.40.6.139"));
		vSeeds.push_back(CDNSSeedData("89.40.12.37", "89.40.12.37"));
		vSeeds.push_back(CDNSSeedData("80.209.228.174", "80.209.228.174"));
		vSeeds.push_back(CDNSSeedData("80.209.236.44", "80.209.236.44"));
		vSeeds.push_back(CDNSSeedData("212.47.227.145", "212.47.227.145"));
		vSeeds.push_back(CDNSSeedData("45.77.138.247", "45.77.138.247"));
		vSeeds.push_back(CDNSSeedData("194.67.208.20", "194.67.208.20"));
		vSeeds.push_back(CDNSSeedData("199.247.28.135", "199.247.28.135"));
		vSeeds.push_back(CDNSSeedData("89.47.161.107", "89.47.161.107"));
		vSeeds.push_back(CDNSSeedData("45.32.229.14", "45.32.229.14"));
		vSeeds.push_back(CDNSSeedData("45.32.115.69", "45.32.115.69"));
		vSeeds.push_back(CDNSSeedData("39.104.57.97", "39.104.57.97"));
		vSeeds.push_back(CDNSSeedData("173.255.199.5", "173.255.199.5"));
		vSeeds.push_back(CDNSSeedData("176.223.129.133", "176.223.129.133"));
		vSeeds.push_back(CDNSSeedData("185.33.146.133", "185.33.146.133"));
		vSeeds.push_back(CDNSSeedData("89.40.15.217", "89.40.15.217"));
		vSeeds.push_back(CDNSSeedData("89.40.3.178", "89.40.3.178"));
		vSeeds.push_back(CDNSSeedData("89.40.8.67", "89.40.8.67"));
		vSeeds.push_back(CDNSSeedData("35.202.153.142", "35.202.153.142"));
		vSeeds.push_back(CDNSSeedData("80.209.227.154", "80.209.227.154"));
		vSeeds.push_back(CDNSSeedData("89.47.166.194", "89.47.166.194"));
		vSeeds.push_back(CDNSSeedData("35.204.232.106", "35.204.232.106"));
		vSeeds.push_back(CDNSSeedData("89.40.12.160", "89.40.12.160"));
		vSeeds.push_back(CDNSSeedData("51.15.135.186", "51.15.135.186"));
		vSeeds.push_back(CDNSSeedData("176.223.129.74", "176.223.129.74"));
		vSeeds.push_back(CDNSSeedData("176.223.135.240", "176.223.135.240"));
		vSeeds.push_back(CDNSSeedData("89.47.160.105", "89.47.160.105"));
		
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0xD6)(0xD8).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strSporkKeyOld = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strObfuscationPoolDummyAddress = "AcmpqXViWUXNroqVNYRdKjKrFM6PNa1oTM";
        nStartMasternodePayments = 1510272000; //11/10/2017 @ 12:00am (UTC)

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 6; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zXLQ to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04e1d34432d3a5803312f33cf20686b1801835ea8efb18ad77d50b5ec1ce5ca73de65c36c082ca5c51880f8ffb5a296d8dc780f1dc02f22eba4dde1816a6a54b75");
        nDefaultPort = 55600;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ALQO: 1 day
        nTargetSpacing = 1 * 60;  // ALQO: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000  * COIN;
        nZerocoinStartHeight = 1000000;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1509321602;
        genesis.nNonce = 343913;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000083eda581357fce6db177da9049ee583b3d32236d4ff52e1f86fee2d5aad"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
        vSeeds.push_back(CDNSSeedData("85.25.138.64", "85.25.138.64"));
        vSeeds.push_back(CDNSSeedData("85.25.251.198", "85.25.251.198"));
        vSeeds.push_back(CDNSSeedData("85.25.251.199", "85.25.251.199"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83); // Testnet alqo addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet alqo script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strSporkKeyOld = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1510272000;
        nBudget_Fee_Confirmations = 3;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // ALQO: 1 day
        nTargetSpacing = 1 * 60;        // ALQO: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1509321603;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 129915;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 55700;
        assert(hashGenesisBlock == uint256("0x00000fea76c2e8523777b3dce649c363b4c5e0234605cae551f8d822d17fcc16"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
