// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
    boost::assign::map_list_of(0, uint256("0x0000083eda581357fce6db177da9049ee583b3d32236d4ff52e1f86fee2d5aad"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1454124731,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000fea76c2e8523777b3dce649c363b4c5e0234605cae551f8d822d17fcc16"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

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
        bnProofOfWorkLimit = ~uint256(0) >> 20; // ALQO starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ALQO: 1 day
        nTargetSpacing = 1 * 60;  // ALQO: 1 minute
        nLastPOWBlock = 475200;
        nMaturity = 110;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 10000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 100000000 * COIN;
		strDeveloperFeePayee = "AG6MCBRozzcQMMi2SXdi4TJhhLeycQERyk";

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
		
		vSeeds.push_back(CDNSSeedData("89.40.1.207", "89.40.1.207"));
		vSeeds.push_back(CDNSSeedData("94.177.163.5", "94.177.163.5"));
		vSeeds.push_back(CDNSSeedData("217.163.28.54", "217.163.28.54"));
		vSeeds.push_back(CDNSSeedData("79.98.24.205", "79.98.24.205"));
		vSeeds.push_back(CDNSSeedData("45.76.62.186", "45.76.62.186"));
		vSeeds.push_back(CDNSSeedData("89.47.160.80", "89.47.160.80"));
		vSeeds.push_back(CDNSSeedData("89.47.164.163", "89.47.164.163"));
		vSeeds.push_back(CDNSSeedData("89.40.10.63", "89.40.10.63"));
		vSeeds.push_back(CDNSSeedData("45.77.200.171", "45.77.200.171"));
		vSeeds.push_back(CDNSSeedData("109.235.69.156", "109.235.69.156"));
		vSeeds.push_back(CDNSSeedData("89.47.160.106", "89.47.160.106"));
		vSeeds.push_back(CDNSSeedData("77.221.153.17", "77.221.153.17"));
		vSeeds.push_back(CDNSSeedData("212.24.111.138", "212.24.111.138"));
		vSeeds.push_back(CDNSSeedData("155.94.226.42", "155.94.226.42"));
		vSeeds.push_back(CDNSSeedData("62.77.153.254", "62.77.153.254"));
		vSeeds.push_back(CDNSSeedData("199.247.15.35", "199.247.15.35"));
		vSeeds.push_back(CDNSSeedData("62.77.158.112", "62.77.158.112"));
		vSeeds.push_back(CDNSSeedData("140.82.45.192", "140.82.45.192"));
		vSeeds.push_back(CDNSSeedData("89.47.167.163", "89.47.167.163"));
		vSeeds.push_back(CDNSSeedData("62.77.158.97", "62.77.158.97"));
		vSeeds.push_back(CDNSSeedData("45.32.221.191", "45.32.221.191"));
		vSeeds.push_back(CDNSSeedData("89.40.12.222", "89.40.12.222"));
		vSeeds.push_back(CDNSSeedData("222.191.227.122", "222.191.227.122"));
		vSeeds.push_back(CDNSSeedData("89.40.8.72", "89.40.8.72"));
		vSeeds.push_back(CDNSSeedData("198.211.114.139", "198.211.114.139"));
		vSeeds.push_back(CDNSSeedData("89.47.162.242", "89.47.162.242"));
		vSeeds.push_back(CDNSSeedData("45.32.158.35", "45.32.158.35"));
		vSeeds.push_back(CDNSSeedData("89.40.11.193", "89.40.11.193"));
		vSeeds.push_back(CDNSSeedData("62.77.152.6", "62.77.152.6"));
		vSeeds.push_back(CDNSSeedData("80.209.235.69", "80.209.235.69"));
		vSeeds.push_back(CDNSSeedData("144.217.192.159", "144.217.192.159"));
		vSeeds.push_back(CDNSSeedData("80.209.237.235", "80.209.237.235"));
		vSeeds.push_back(CDNSSeedData("94.16.122.215", "94.16.122.215"));
		vSeeds.push_back(CDNSSeedData("188.68.55.90", "188.68.55.90"));
		vSeeds.push_back(CDNSSeedData("95.216.142.83", "95.216.142.83"));
		vSeeds.push_back(CDNSSeedData("8.9.8.100", "8.9.8.100"));
		vSeeds.push_back(CDNSSeedData("104.156.225.204", "104.156.225.204"));
		vSeeds.push_back(CDNSSeedData("62.77.159.144", "62.77.159.144"));
		vSeeds.push_back(CDNSSeedData("194.135.81.126", "194.135.81.126"));
		vSeeds.push_back(CDNSSeedData("188.201.198.114", "188.201.198.114"));
		vSeeds.push_back(CDNSSeedData("80.209.238.227", "80.209.238.227"));
		vSeeds.push_back(CDNSSeedData("59.42.89.34", "59.42.89.34"));
		vSeeds.push_back(CDNSSeedData("62.77.156.93", "62.77.156.93"));
		vSeeds.push_back(CDNSSeedData("62.77.158.105", "62.77.158.105"));
		vSeeds.push_back(CDNSSeedData("62.77.156.218", "62.77.156.218"));
		vSeeds.push_back(CDNSSeedData("144.202.90.68", "144.202.90.68"));
		vSeeds.push_back(CDNSSeedData("45.77.185.13", "45.77.185.13"));
		vSeeds.push_back(CDNSSeedData("174.138.4.156", "174.138.4.156"));
		vSeeds.push_back(CDNSSeedData("47.92.1.214", "47.92.1.214"));
		vSeeds.push_back(CDNSSeedData("89.47.160.109", "89.47.160.109"));
		vSeeds.push_back(CDNSSeedData("94.176.234.190", "94.176.234.190"));
		vSeeds.push_back(CDNSSeedData("89.40.12.59", "89.40.12.59"));
		vSeeds.push_back(CDNSSeedData("89.40.13.68", "89.40.13.68"));
		vSeeds.push_back(CDNSSeedData("209.250.254.244", "209.250.254.244"));
		vSeeds.push_back(CDNSSeedData("140.82.34.161", "140.82.34.161"));
		vSeeds.push_back(CDNSSeedData("80.208.226.210", "80.208.226.210"));
		vSeeds.push_back(CDNSSeedData("94.176.239.106", "94.176.239.106"));
		vSeeds.push_back(CDNSSeedData("89.40.12.105", "89.40.12.105"));
		vSeeds.push_back(CDNSSeedData("208.167.248.144", "208.167.248.144"));
		vSeeds.push_back(CDNSSeedData("62.77.152.7", "62.77.152.7"));
		vSeeds.push_back(CDNSSeedData("89.47.165.1", "89.47.165.1"));
		vSeeds.push_back(CDNSSeedData("108.61.222.196", "108.61.222.196"));
		vSeeds.push_back(CDNSSeedData("52.91.63.63", "52.91.63.63"));
		vSeeds.push_back(CDNSSeedData("45.76.206.87", "45.76.206.87"));
		vSeeds.push_back(CDNSSeedData("89.47.165.159", "89.47.165.159"));
		vSeeds.push_back(CDNSSeedData("207.246.87.163", "207.246.87.163"));
		vSeeds.push_back(CDNSSeedData("89.40.4.112", "89.40.4.112"));
		vSeeds.push_back(CDNSSeedData("144.202.102.75", "144.202.102.75"));
		vSeeds.push_back(CDNSSeedData("80.209.233.43", "80.209.233.43"));
		vSeeds.push_back(CDNSSeedData("159.65.64.48", "159.65.64.48"));
		vSeeds.push_back(CDNSSeedData("45.32.193.236", "45.32.193.236"));
		vSeeds.push_back(CDNSSeedData("89.40.3.82", "89.40.3.82"));
		vSeeds.push_back(CDNSSeedData("89.40.1.54", "89.40.1.54"));
		vSeeds.push_back(CDNSSeedData("209.250.236.185", "209.250.236.185"));
		vSeeds.push_back(CDNSSeedData("89.47.160.76", "89.47.160.76"));
		vSeeds.push_back(CDNSSeedData("45.77.111.95", "45.77.111.95"));
		vSeeds.push_back(CDNSSeedData("62.77.156.222", "62.77.156.222"));
		vSeeds.push_back(CDNSSeedData("89.40.3.81", "89.40.3.81"));
		vSeeds.push_back(CDNSSeedData("80.208.227.222", "80.208.227.222"));
		vSeeds.push_back(CDNSSeedData("209.250.239.53", "209.250.239.53"));
		vSeeds.push_back(CDNSSeedData("45.77.116.80", "45.77.116.80"));
		vSeeds.push_back(CDNSSeedData("45.32.89.163", "45.32.89.163"));
		vSeeds.push_back(CDNSSeedData("103.57.209.83", "103.57.209.83"));
		vSeeds.push_back(CDNSSeedData("80.209.224.163", "80.209.224.163"));
		vSeeds.push_back(CDNSSeedData("62.77.155.147", "62.77.155.147"));
		vSeeds.push_back(CDNSSeedData("80.209.224.146", "80.209.224.146"));
		vSeeds.push_back(CDNSSeedData("63.142.252.48", "63.142.252.48"));
		vSeeds.push_back(CDNSSeedData("199.247.14.150", "199.247.14.150"));
		vSeeds.push_back(CDNSSeedData("120.27.234.36", "120.27.234.36"));
		vSeeds.push_back(CDNSSeedData("209.250.227.43", "209.250.227.43"));
		vSeeds.push_back(CDNSSeedData("45.76.32.121", "45.76.32.121"));
		vSeeds.push_back(CDNSSeedData("159.65.240.84", "159.65.240.84"));
		vSeeds.push_back(CDNSSeedData("45.77.201.188", "45.77.201.188"));
		vSeeds.push_back(CDNSSeedData("80.209.237.211", "80.209.237.211"));
		vSeeds.push_back(CDNSSeedData("89.40.6.147", "89.40.6.147"));
		vSeeds.push_back(CDNSSeedData("158.69.202.48", "158.69.202.48"));
		vSeeds.push_back(CDNSSeedData("209.250.247.31", "209.250.247.31"));
		vSeeds.push_back(CDNSSeedData("47.97.166.99", "47.97.166.99"));
		vSeeds.push_back(CDNSSeedData("108.61.170.252", "108.61.170.252"));
		vSeeds.push_back(CDNSSeedData("45.76.92.72", "45.76.92.72"));
		vSeeds.push_back(CDNSSeedData("89.40.6.253", "89.40.6.253"));
		vSeeds.push_back(CDNSSeedData("89.40.8.77", "89.40.8.77"));
		vSeeds.push_back(CDNSSeedData("89.40.11.140", "89.40.11.140"));
		vSeeds.push_back(CDNSSeedData("51.15.46.223", "51.15.46.223"));
		vSeeds.push_back(CDNSSeedData("195.201.34.154", "195.201.34.154"));
		vSeeds.push_back(CDNSSeedData("47.92.137.156", "47.92.137.156"));
		vSeeds.push_back(CDNSSeedData("89.40.0.251", "89.40.0.251"));
		vSeeds.push_back(CDNSSeedData("62.77.157.14", "62.77.157.14"));
		vSeeds.push_back(CDNSSeedData("62.77.155.200", "62.77.155.200"));
		vSeeds.push_back(CDNSSeedData("45.77.211.106", "45.77.211.106"));
		vSeeds.push_back(CDNSSeedData("107.174.233.131", "107.174.233.131"));
		vSeeds.push_back(CDNSSeedData("195.181.241.25", "195.181.241.25"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("160.19.48.213", "160.19.48.213"));
		vSeeds.push_back(CDNSSeedData("80.209.239.43", "80.209.239.43"));
		vSeeds.push_back(CDNSSeedData("80.209.232.40", "80.209.232.40"));
		vSeeds.push_back(CDNSSeedData("45.32.136.85", "45.32.136.85"));
		vSeeds.push_back(CDNSSeedData("139.99.120.25", "139.99.120.25"));
		vSeeds.push_back(CDNSSeedData("167.99.34.19", "167.99.34.19"));
		vSeeds.push_back(CDNSSeedData("89.47.160.65", "89.47.160.65"));
		vSeeds.push_back(CDNSSeedData("194.135.94.188", "194.135.94.188"));
		vSeeds.push_back(CDNSSeedData("140.82.1.146", "140.82.1.146"));
		vSeeds.push_back(CDNSSeedData("86.121.208.47", "86.121.208.47"));
		vSeeds.push_back(CDNSSeedData("108.61.211.98", "108.61.211.98"));
		vSeeds.push_back(CDNSSeedData("89.40.6.145", "89.40.6.145"));
		vSeeds.push_back(CDNSSeedData("178.32.113.197", "178.32.113.197"));
		vSeeds.push_back(CDNSSeedData("54.37.157.60", "54.37.157.60"));
		vSeeds.push_back(CDNSSeedData("89.40.13.175", "89.40.13.175"));
		vSeeds.push_back(CDNSSeedData("89.40.6.210", "89.40.6.210"));
		vSeeds.push_back(CDNSSeedData("89.40.5.40", "89.40.5.40"));
		vSeeds.push_back(CDNSSeedData("80.209.235.164", "80.209.235.164"));
		vSeeds.push_back(CDNSSeedData("120.79.190.251", "120.79.190.251"));
		vSeeds.push_back(CDNSSeedData("188.68.45.227", "188.68.45.227"));
		vSeeds.push_back(CDNSSeedData("89.47.166.64", "89.47.166.64"));
		vSeeds.push_back(CDNSSeedData("94.176.238.216", "94.176.238.216"));
		vSeeds.push_back(CDNSSeedData("80.209.226.48", "80.209.226.48"));
		vSeeds.push_back(CDNSSeedData("209.250.232.224", "209.250.232.224"));
		vSeeds.push_back(CDNSSeedData("89.40.3.86", "89.40.3.86"));
		vSeeds.push_back(CDNSSeedData("195.201.141.227", "195.201.141.227"));
		vSeeds.push_back(CDNSSeedData("89.40.6.148", "89.40.6.148"));
		vSeeds.push_back(CDNSSeedData("68.232.175.18", "68.232.175.18"));
		vSeeds.push_back(CDNSSeedData("89.40.10.76", "89.40.10.76"));
		vSeeds.push_back(CDNSSeedData("47.92.83.66", "47.92.83.66"));
		vSeeds.push_back(CDNSSeedData("47.254.31.178", "47.254.31.178"));
		vSeeds.push_back(CDNSSeedData("194.182.80.150", "194.182.80.150"));
		vSeeds.push_back(CDNSSeedData("195.181.242.102", "195.181.242.102"));
		vSeeds.push_back(CDNSSeedData("209.250.236.176", "209.250.236.176"));
		vSeeds.push_back(CDNSSeedData("89.47.161.150", "89.47.161.150"));
		vSeeds.push_back(CDNSSeedData("89.40.13.117", "89.40.13.117"));
		vSeeds.push_back(CDNSSeedData("62.77.156.225", "62.77.156.225"));
		vSeeds.push_back(CDNSSeedData("45.32.42.43", "45.32.42.43"));
		vSeeds.push_back(CDNSSeedData("80.209.235.239", "80.209.235.239"));
		vSeeds.push_back(CDNSSeedData("89.47.164.15", "89.47.164.15"));
		vSeeds.push_back(CDNSSeedData("47.92.75.41", "47.92.75.41"));
		vSeeds.push_back(CDNSSeedData("207.246.116.37", "207.246.116.37"));
		vSeeds.push_back(CDNSSeedData("212.24.100.157", "212.24.100.157"));
		vSeeds.push_back(CDNSSeedData("35.201.242.160", "35.201.242.160"));
		vSeeds.push_back(CDNSSeedData("103.57.209.83", "103.57.209.83"));
		vSeeds.push_back(CDNSSeedData("89.47.160.243", "89.47.160.243"));
		vSeeds.push_back(CDNSSeedData("80.209.230.80", "80.209.230.80"));
		vSeeds.push_back(CDNSSeedData("207.148.12.14", "207.148.12.14"));
		vSeeds.push_back(CDNSSeedData("199.247.17.200", "199.247.17.200"));
		vSeeds.push_back(CDNSSeedData("195.181.242.100", "195.181.242.100"));
		vSeeds.push_back(CDNSSeedData("45.76.142.145", "45.76.142.145"));
		vSeeds.push_back(CDNSSeedData("80.208.224.92", "80.208.224.92"));
		vSeeds.push_back(CDNSSeedData("103.57.208.58", "103.57.208.58"));
		vSeeds.push_back(CDNSSeedData("45.77.73.37", "45.77.73.37"));
		vSeeds.push_back(CDNSSeedData("104.238.173.130", "104.238.173.130"));
		vSeeds.push_back(CDNSSeedData("80.209.229.222", "80.209.229.222"));
		vSeeds.push_back(CDNSSeedData("45.77.149.54", "45.77.149.54"));
		vSeeds.push_back(CDNSSeedData("62.77.158.98", "62.77.158.98"));
		vSeeds.push_back(CDNSSeedData("45.77.86.233", "45.77.86.233"));
		vSeeds.push_back(CDNSSeedData("89.40.8.213", "89.40.8.213"));
		vSeeds.push_back(CDNSSeedData("89.40.5.42", "89.40.5.42"));
		vSeeds.push_back(CDNSSeedData("89.46.70.77", "89.46.70.77"));
		vSeeds.push_back(CDNSSeedData("62.77.157.189", "62.77.157.189"));
		vSeeds.push_back(CDNSSeedData("172.104.156.90", "172.104.156.90"));
		vSeeds.push_back(CDNSSeedData("194.135.89.67", "194.135.89.67"));
		vSeeds.push_back(CDNSSeedData("80.209.235.152", "80.209.235.152"));
		vSeeds.push_back(CDNSSeedData("194.135.81.206", "194.135.81.206"));
		vSeeds.push_back(CDNSSeedData("103.230.158.57", "103.230.158.57"));
		vSeeds.push_back(CDNSSeedData("80.209.237.127", "80.209.237.127"));
		vSeeds.push_back(CDNSSeedData("209.250.233.241", "209.250.233.241"));
		vSeeds.push_back(CDNSSeedData("209.250.236.119", "209.250.236.119"));
		vSeeds.push_back(CDNSSeedData("62.77.157.172", "62.77.157.172"));
		vSeeds.push_back(CDNSSeedData("62.77.153.113", "62.77.153.113"));
		vSeeds.push_back(CDNSSeedData("80.209.229.38", "80.209.229.38"));
		vSeeds.push_back(CDNSSeedData("62.77.157.181", "62.77.157.181"));
		vSeeds.push_back(CDNSSeedData("208.167.255.210", "208.167.255.210"));
		vSeeds.push_back(CDNSSeedData("62.77.159.153", "62.77.159.153"));
		vSeeds.push_back(CDNSSeedData("138.201.152.149", "138.201.152.149"));
		vSeeds.push_back(CDNSSeedData("89.40.2.65", "89.40.2.65"));
		vSeeds.push_back(CDNSSeedData("45.77.59.206", "45.77.59.206"));
		vSeeds.push_back(CDNSSeedData("89.40.1.91", "89.40.1.91"));
		vSeeds.push_back(CDNSSeedData("163.172.166.59", "163.172.166.59"));
		vSeeds.push_back(CDNSSeedData("80.208.225.216", "80.208.225.216"));
		vSeeds.push_back(CDNSSeedData("94.176.235.8", "94.176.235.8"));
		vSeeds.push_back(CDNSSeedData("62.77.153.22", "62.77.153.22"));
		vSeeds.push_back(CDNSSeedData("51.15.4.242", "51.15.4.242"));
		vSeeds.push_back(CDNSSeedData("89.40.5.53", "89.40.5.53"));
		

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
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
        strDarksendPoolDummyAddress = "AcmpqXViWUXNroqVNYRdKjKrFM6PNa1oTM";
        nStartMasternodePayments = 1510272000; //11/10/2017 @ 12:00am (UTC)
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
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;

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
		
        vSeeds.push_back(CDNSSeedData("80.209.227.9", "80.209.227.9"));
        vSeeds.push_back(CDNSSeedData("80.209.228.190", "80.209.228.190"));
        vSeeds.push_back(CDNSSeedData("80.209.228.191", "80.209.228.191"));
        vSeeds.push_back(CDNSSeedData("80.209.228.192", "80.209.228.192"));
        vSeeds.push_back(CDNSSeedData("80.209.228.193", "80.209.228.193"));
        vSeeds.push_back(CDNSSeedData("80.209.228.189", "80.209.228.189"));
        vSeeds.push_back(CDNSSeedData("80.209.228.194", "80.209.228.194"));
        vSeeds.push_back(CDNSSeedData("80.209.228.197", "80.209.228.197"));
        vSeeds.push_back(CDNSSeedData("80.209.228.196", "80.209.228.196"));
        vSeeds.push_back(CDNSSeedData("80.209.228.195", "80.209.228.195"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet alqo BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet alqo BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet alqo BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 2;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1510272000;
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

        fRequireRPCPassword = false;
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

        fRequireRPCPassword = false;
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
