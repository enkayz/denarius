// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = nCoinbaseMaturity * 2; // twice of coin maturity is a long enough chain

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,       hashGenesisBlock )
        ( 2000,    uint256("0x0000000003d697d683fcbf6041139dd24ebf93089ad9ce1ac49dea99fcee2818") )
        ( 5000,    uint256("0x000000000324161ad72079927d9b5a317a93f63bd0c4f28ad89046dd25373fad") )
        ( 10000,   uint256("0x00000000058989f94843c6047bdf72b3f37f62055354c5ff859e28bb0b5282b9") )
        ( 20000,   uint256("0x00000000000420ca6af3e3e90066c806ac033ed963247adf566b7397122e2c8a") )
        ( 30000,   uint256("0x000000000282bafc3e63bb0f86134329de9ff387d04764ad6a4ca700c47fbf7e") )
        ( 50000,   uint256("0x00000000000b5e89366f583548f77c0e88476d6ff1ddd4b391d00ec7fd1d4bb3") )
        ( 75009,   uint256("0x00000000004b4ca508c4006f9163b479b4c6599e5949140bca835da1ff1234fd") )
        ( 104999,  uint256("0x0000000000116592035fde4848d187a48a67a37c2a8e3e6c12150e40121054d8") )
        ( 144999,  uint256("0x00000000008509564a6a3fb42a9f9d77a93218e1c5738758cb6753fc03dee1ae") )
        ( 150001,  uint256("0x00000000005aaad7814e1eb4ec9c2e33846078f80b45a99e3f37cb6c3b1e07bd") )
        ( 175503,  uint256("0x0000000000f6e716fd9c763077337499fea706bf1012c6617991c0f0699e92fc") )
        ( 195500,  uint256("0x00000000000125265e79f31c6aa19d2f5db5391d41416d4d44aa675dd205acfa") )
        ( 249999,  uint256("0x0000000000200eaf8ce9cc5ebb5e623fac9da021c11fc8e5f7db91a74004a53d") )
        ( 260001,  uint256("0x0000000000ac126bfc1d9d9af9b2bb6d5063e5f2d6144e3b0fae40e04ec350c2") )
        ( 271836,  uint256("0x00000000004397a1b2c812695093c437667665337a3c11c652b616a1ee1efe89") )
        ( 280140,  uint256("0x000000000026b26dc0bdd088e0cf7c86e845ae2c115170460e5440e092a75017") )
        ( 300000,  uint256("0x0000000000b52718d9b5eab10aa7757a5d6f7b17bfd85c68cbb2f83f6577a5ed") )
        ( 320000,  uint256("0x0000000000218a6999d1c922b7d4e04f79be3e1e90ec139789851651d5d8d39e") )
        ( 351430,  uint256("0x0000000000901ce4a4cf6849515142cb2af344730f9fe16e77f456eb2bfccdc7") )
        ( 380001,  uint256("0x0000000000b8d93082b7bca98042839dc5c57c059eaf81fad137db137115cb22") )
        ( 400000,  uint256("0x00000000005d6a6ad52162db36954af6651a1edb8189f850116f7f8ec85f507b") )
        ( 440001,  uint256("0x00000000000438fd4ee164c095d16ad8f8fd5a036f6d21a2ffd5e07309fe1132") )
        ( 480000,  uint256("0x0000000000242586fe6aac7718830ae9a397aa8960b9fabd95b924d3cdfa183c") )
        ( 519998,  uint256("0x00000000001da6bd8bac044f8d6a17d6d2aac59c49ea61556d35abc872bfdbfb") )
        ( 560007,  uint256("0x0000000000025219f9002ca2529d58b89890c4e5c984d39653daf01cbb2dcf4f") )
        ( 584682,  uint256("0x000000000007e848f9cba04a7ba99c9882ed377fecd36848d4e391f90dd739d2") )
        ( 600000,  uint256("0x000000000003de26b4aaaf400c816e2bb2b2b75c16653e5428330f98438eb7ca") )
        ( 608581,  uint256("0x000000000005b26af64dda3e172bef208342295fabfd916165211518eb7f8ad7") )
        ( 625114,  uint256("0x000000000024290e8a2919d4b5ecb915892648df2f362d3136391e8b9f542a9c") )
        ( 636115,  uint256("0x000000000002e90ba8bd7737b206c75a48cafef514e640b7c03753e93fb5fffe") )
        ( 640042,  uint256("0x000000000010014c70f1eef2e6a0599b4c05f19e3dc0510758c684eaec513a28") )
        ( 641361,  uint256("0x000000000005e6b7e106ce402511a64b239b5668e3599fb9e71dd75c16528033") )
        ( 654900,  uint256("0x000000000003200e2a80124060eab0f846671ec542cfa8f19f1bf4ad9501ad3e") )
        ( 695732,  uint256("0x000000000039800dffda8f76c6fc46db0e0fc585274d34d3377058a7ae4be093") )
        ( 705320,  uint256("0x00000000002759fa23cc4e06f8356086bb842f8083be877c246ea44ca9cb5fad") )
        ( 715006,  uint256("0x000000000040fcb3164c963fb3031f8d73b519d3f181dde0fbd1c00280a9202f") )
        ( 735000,  uint256("0x000000000026ee4128cd6cc718bcd6e346e83be573cbc1bd7aba846e4f843939") )
        ( 755516,  uint256("0x00000000000a4c4951f38632c593cdd6c12fc3df3f8eb483f97cb6152589fbdb") )
        ( 800104,  uint256("0x00000000003c03a429dfa8a6e7343323a7b348b6875d3603e50ac5298749754e") )
        ( 843547,  uint256("0x0000000000088b367232bbca1ca217d8d29f8cd1e7487e4f7d2bcea6412b4ce8") )
        ( 1451336, uint256("0x000000000012badc99e6d0a8409fc756955206236b9634494efad2ae81a35634") )
        ( 1451337, uint256("0x000000000050371cb4560ff3cf6f0d00407855087700b08766609777b72d5ad3") )
        ( 1451338, uint256("0x000000000001c79e7044e8498c3f2ca744b7d36cd9778690f77e78df5d010508") )
        ( 1451400, uint256("0x0000000000273ea9866138cabadbc7c2fa2c8a9def4039b38a3a89cbf97a1149") )
        ( 1451450, uint256("0x76db875344d45caf01c3443528a87d27e200ffcfd82215141f595f9572020e22") )
        ( 1451700, uint256("0x00000000005bdfdd13507c1d462267ca777f9e831d5c2e7db126c6ae6f6c33e3") )
        ( 1451900, uint256("0x00000000001c38d56da0e1ec3867bbebb7dec0219d3c49a190751a014e553a42") )
        ( 1452000, uint256("0x000000000027d29b973e41900006d4a95806f8af252493dc9f83be2890066e05") )
        ( 1452101, uint256("0x000000000003d8306c36bc9b165ce428f259cc37c79d6dde43cbf8af339f372d") )
        ( 1452201, uint256("0x0000000000430610f8cbd7797e1c00273b25ed3f108be352efa2f24e070fad52") )
        ( 1452301, uint256("0x00000000003a49107cfb3d279135983d5010b1c253dd08c776c5a32eb5f6e0d4") )
        ( 1452400, uint256("0x000000000002b38847f90b5017caf6bd8cc824ad70ea58461bcca86be69d54ce") )
        ( 1452400, uint256("0x000000000002b38847f90b5017caf6bd8cc824ad70ea58461bcca86be69d54ce") )
        ( 1452506, uint256("0x000000000027e69bba1670e2192fe1b038f5ceed6e52427827da14c37c163ec5") )
        ( 1452860, uint256("0x00000000285f3a8877189bb6b5f18fbf4e301eeda780206b732cea4126f2613f") )
        ( 1453174, uint256("0x0000000004d8cc15c5801d7bf54351c0e8ea2c6e11f5e9d57f18fdec563cab36") )
        ( 1453228, uint256("0x000000000073a61cceb9b7c2b431ccdb7cf32d56860dd6f20e598458fb3df091") )
        ( 1453277, uint256("0x00000000016e4ec6eab324ca1d60bc2ed8b99cb97dac31ef1f560f1bb0385869") )
        ( 1453278, uint256("0x0000000000bed7a5bd91ebc4d33890607725286474787ad6dcf2220002322d0e") )
        ( 1453327, uint256("0x0000000002561470527b4efb92e47b4ab2d4e0dd7c315e6ba676384e7596e43e") )
        ( 1453349, uint256("0x00000000010f41d30c5a18f0a5753ccbc22a0b3e7d483fbdf076b398fc2aa6b3") )
        ( 1453377, uint256("0x00000000005049a3b558e79c1dbea5f1ac250192e02690c810653e6e7dcdb8f5") )
        ( 1453399, uint256("0x00000000027efc2d3e2990bc927dba4d972fe7c5fd29b1394ae24049a1da9e72") )
        ( 1453400, uint256("0x0000000000adfe47f85d8ab1e9c801e491d8d527ad2ebd359e267b6ca72dc51b") )
        ( 1453450, uint256("0x00000000002387facc6fe470048edaea876c8a9bcae2a1c88e23d6798f2caa50") )
        ( 1453520, uint256("0x000000000022640ef130a04f47fd832b754585b056d66672c89bb4022bbd5e1e") )
        ( 1455505, uint256("0x00000000006a1b4a065cb2864bcc57968e8723a6732b788cfd79df81b083da1d") )
        ( 1457120, uint256("0x00000000001d53a4fc1502ea488a88dcac4c77c904175a472cf4fac88ba54fcf") )
        ( 1459471, uint256("0x00000000004eb60d5ea4625ed00f5a7a2f81c460dc86d8d491feb1c0a421e6c7") )
        ( 1461100, uint256("0x00000000000323eb70adfcb3546601cf7e3ae1fc4e5312f03245fcba2c2a1768") )
      //
	;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
    ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // ppcoin: synchronized checkpoint (centrally broadcasted)
    uint256 hashSyncCheckpoint = 0;
    uint256 hashPendingCheckpoint = 0;
    CSyncCheckpoint checkpointMessage;
    CSyncCheckpoint checkpointMessagePending;
    uint256 hashInvalidCheckpoint = 0;
    CCriticalSection cs_hashSyncCheckpoint;

    // ppcoin: get last synchronized checkpoint
    CBlockIndex* GetLastSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            error("GetSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString().c_str());
        else
            return mapBlockIndex[hashSyncCheckpoint];
        return NULL;
    }

    // ppcoin: only descendant of current sync-checkpoint is allowed
    bool ValidateSyncCheckpoint(uint256 hashCheckpoint)
    {
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString().c_str());
        if (!mapBlockIndex.count(hashCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for received sync-checkpoint %s", hashCheckpoint.ToString().c_str());

        CBlockIndex* pindexSyncCheckpoint = mapBlockIndex[hashSyncCheckpoint];
        CBlockIndex* pindexCheckpointRecv = mapBlockIndex[hashCheckpoint];

        if (pindexCheckpointRecv->nHeight <= pindexSyncCheckpoint->nHeight)
        {
            // Received an older checkpoint, trace back from current checkpoint
            // to the same height of the received checkpoint to verify
            // that current checkpoint should be a descendant block
            CBlockIndex* pindex = pindexSyncCheckpoint;
            while (pindex->nHeight > pindexCheckpointRecv->nHeight)
                if (!(pindex = pindex->pprev))
                    return error("ValidateSyncCheckpoint: pprev null - block index structure failure");
            if (pindex->GetBlockHash() != hashCheckpoint)
            {
                hashInvalidCheckpoint = hashCheckpoint;
                return error("ValidateSyncCheckpoint: new sync-checkpoint %s is conflicting with current sync-checkpoint %s", hashCheckpoint.ToString().c_str(), hashSyncCheckpoint.ToString().c_str());
            }
            return false; // ignore older checkpoint
        }

        // Received checkpoint should be a descendant block of the current
        // checkpoint. Trace back to the same height of current checkpoint
        // to verify.
        CBlockIndex* pindex = pindexCheckpointRecv;
        while (pindex->nHeight > pindexSyncCheckpoint->nHeight)
            if (!(pindex = pindex->pprev))
                return error("ValidateSyncCheckpoint: pprev2 null - block index structure failure");
        if (pindex->GetBlockHash() != hashSyncCheckpoint)
        {
            hashInvalidCheckpoint = hashCheckpoint;
            return error("ValidateSyncCheckpoint: new sync-checkpoint %s is not a descendant of current sync-checkpoint %s", hashCheckpoint.ToString().c_str(), hashSyncCheckpoint.ToString().c_str());
        }
        return true;
    }

    bool WriteSyncCheckpoint(const uint256& hashCheckpoint)
    {
        CTxDB txdb;
        txdb.TxnBegin();
        if (!txdb.WriteSyncCheckpoint(hashCheckpoint))
        {
            txdb.TxnAbort();
            return error("WriteSyncCheckpoint(): failed to write to db sync checkpoint %s", hashCheckpoint.ToString().c_str());
        }
        if (!txdb.TxnCommit())
            return error("WriteSyncCheckpoint(): failed to commit to db sync checkpoint %s", hashCheckpoint.ToString().c_str());

        Checkpoints::hashSyncCheckpoint = hashCheckpoint;
        return true;
    }

    bool AcceptPendingSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint != 0 && mapBlockIndex.count(hashPendingCheckpoint))
        {
            if (!ValidateSyncCheckpoint(hashPendingCheckpoint))
            {
                hashPendingCheckpoint = 0;
                checkpointMessagePending.SetNull();
                return false;
            }

            CTxDB txdb;
            CBlockIndex* pindexCheckpoint = mapBlockIndex[hashPendingCheckpoint];
            if (!pindexCheckpoint->IsInMainChain())
            {
                CBlock block;
                if (!block.ReadFromDisk(pindexCheckpoint))
                    return error("AcceptPendingSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
                if (!block.SetBestChain(txdb, pindexCheckpoint))
                {
                    hashInvalidCheckpoint = hashPendingCheckpoint;
                    return error("AcceptPendingSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
                }
            }

            if (!WriteSyncCheckpoint(hashPendingCheckpoint))
                return error("AcceptPendingSyncCheckpoint(): failed to write sync checkpoint %s", hashPendingCheckpoint.ToString().c_str());
            hashPendingCheckpoint = 0;
            checkpointMessage = checkpointMessagePending;
            checkpointMessagePending.SetNull();
            printf("AcceptPendingSyncCheckpoint : sync-checkpoint at %s\n", hashSyncCheckpoint.ToString().c_str());
            // relay the checkpoint
            if (!checkpointMessage.IsNull())
            {
                BOOST_FOREACH(CNode* pnode, vNodes)
                    checkpointMessage.RelayTo(pnode);
            }
            return true;
        }
        return false;
    }


    // Automatically select a suitable sync-checkpoint
    const CBlockIndex*  AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && (pindex->GetBlockTime() + nCheckpointSpan * nTargetSpacing > pindexBest->GetBlockTime() || pindex->nHeight + nCheckpointSpan > pindexBest->nHeight))
            pindex = pindex->pprev;
        return pindex;
    }

    // Check the chain this block is going to attach to is valid past maturity
    bool CheckSync(const uint256& hashBlock, const CBlockIndex* pindexPrev)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        int nHeight = pindexPrev->nHeight + 1;
        if (IsInitialBlockDownload()) { // Do a basic check if we are catching up
            const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
            if (nHeight <= pindexSync->nHeight){
                return false; // lower height than auto checkpoint
            }
            return true;
        } else { // do a more thorough check when we are already synced
            LOCK(cs_hashSyncCheckpoint);
            // sync-checkpoint should always be accepted block
            assert(mapBlockIndex.count(hashSyncCheckpoint));
            const CBlockIndex* pindexSync = mapBlockIndex[hashSyncCheckpoint];

            if (nHeight > pindexSync->nHeight)
            {
                // trace back to same height as sync-checkpoint
                const CBlockIndex* pindex = pindexPrev;
                while (pindex->nHeight > pindexSync->nHeight)
                    if (!(pindex = pindex->pprev))
                        return error("CheckSync: pprev null - block index structure failure");
                if (pindex->nHeight < pindexSync->nHeight || pindex->GetBlockHash() != hashSyncCheckpoint)
                    return false; // only descendant of sync-checkpoint can pass check
            }
            if (nHeight == pindexSync->nHeight && hashBlock != hashSyncCheckpoint)
                return false; // same height with sync-checkpoint
            if (nHeight < pindexSync->nHeight && !mapBlockIndex.count(hashBlock))
                return false; // lower height than sync-checkpoint
            return true;
        }
    }

    bool WantedByPendingSyncCheckpoint(uint256 hashBlock)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint == 0)
            return false;
        if (hashBlock == hashPendingCheckpoint)
            return true;
        if (mapOrphanBlocks.count(hashPendingCheckpoint)
            && hashBlock == WantedByOrphan(mapOrphanBlocks[hashPendingCheckpoint]))
            return true;
        return false;
    }

    // ppcoin: reset synchronized checkpoint to last hardened checkpoint
    bool ResetSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        const uint256& hash = mapCheckpoints.rbegin()->second;
        if (mapBlockIndex.count(hash) && !mapBlockIndex[hash]->IsInMainChain())
        {
            // checkpoint block accepted but not yet in main chain
            printf("ResetSyncCheckpoint: SetBestChain to hardened checkpoint %s\n", hash.ToString().c_str());
            CTxDB txdb;
            CBlock block;
            if (!block.ReadFromDisk(mapBlockIndex[hash]))
                return error("ResetSyncCheckpoint: ReadFromDisk failed for hardened checkpoint %s", hash.ToString().c_str());
            if (!block.SetBestChain(txdb, mapBlockIndex[hash]))
            {
                return error("ResetSyncCheckpoint: SetBestChain failed for hardened checkpoint %s", hash.ToString().c_str());
            }
        }
        else if(!mapBlockIndex.count(hash))
        {
            // checkpoint block not yet accepted
            hashPendingCheckpoint = hash;
            checkpointMessagePending.SetNull();
            printf("ResetSyncCheckpoint: pending for sync-checkpoint %s\n", hashPendingCheckpoint.ToString().c_str());
        }

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            if (mapBlockIndex.count(hash) && mapBlockIndex[hash]->IsInMainChain())
            {
                if (!WriteSyncCheckpoint(hash))
                    return error("ResetSyncCheckpoint: failed to write sync checkpoint %s", hash.ToString().c_str());
                printf("ResetSyncCheckpoint: sync-checkpoint reset to %s\n", hashSyncCheckpoint.ToString().c_str());
                return true;
            }
        }

        return false;
    }

    void AskForPendingSyncCheckpoint(CNode* pfrom)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (pfrom && hashPendingCheckpoint != 0 && (!mapBlockIndex.count(hashPendingCheckpoint)) && (!mapOrphanBlocks.count(hashPendingCheckpoint)))
            pfrom->AskFor(CInv(MSG_BLOCK, hashPendingCheckpoint));
    }

    bool SetCheckpointPrivKey(std::string strPrivKey)
    {
        if (fDebug)
            printf("SetCheckpointPrivKey()\n");

        // Test signing a sync-checkpoint with genesis block
        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = !fTestNet ? hashGenesisBlock : hashGenesisBlockTestNet;
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        std::vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()),false); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return false;

        // Test signing successful, proceed
        CSyncCheckpoint::strMasterPrivKey = strPrivKey;
        return true;
    }

    bool SendSyncCheckpoint(uint256 hashCheckpoint)
    {
        if (fDebug)
            printf("SendSyncCheckpoint()\n");

        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = hashCheckpoint;
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        if (CSyncCheckpoint::strMasterPrivKey.empty())
            return error("SendSyncCheckpoint: Checkpoint master key unavailable.");
        std::vector<unsigned char> vchPrivKey = ParseHex(CSyncCheckpoint::strMasterPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()), false); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return error("SendSyncCheckpoint: Unable to sign checkpoint, check private key?");

        if (!checkpoint.ProcessSyncCheckpoint(NULL))
        {
            printf("WARNING: SendSyncCheckpoint: Failed to process checkpoint.\n");
            return false;
        }

        // Relay checkpoint
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes)
                checkpoint.RelayTo(pnode);
        }
        return true;
    }

    // Is the sync-checkpoint outside maturity window?
    bool IsMatureSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        // sync-checkpoint should always be accepted block
        assert(mapBlockIndex.count(hashSyncCheckpoint));
        const CBlockIndex* pindexSync = mapBlockIndex[hashSyncCheckpoint];
        return (nBestHeight >= pindexSync->nHeight + nCoinbaseMaturity ||
                pindexSync->GetBlockTime() + nStakeMinAge < GetAdjustedTime());
    }
}

// ppcoin: sync-checkpoint master key
const std::string CSyncCheckpoint::strMasterPubKey = "02334512c0d7a9a69289c4b7ad1c76e5330ef9dacd9da912c91a853986bddf0434";

std::string CSyncCheckpoint::strMasterPrivKey = "";

// ppcoin: verify signature of sync-checkpoint message
bool CSyncCheckpoint::CheckSignature()
{
    CPubKey key(ParseHex(CSyncCheckpoint::strMasterPubKey));
    if (!key.Verify(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
        return error("CSyncCheckpoint::CheckSignature() : verify signature failed");

    // Now unserialize the data
    CDataStream sMsg(vchMsg, SER_NETWORK, PROTOCOL_VERSION);
    sMsg >> *(CUnsignedSyncCheckpoint*)this;
    return true;
}

// ppcoin: process synchronized checkpoint
bool CSyncCheckpoint::ProcessSyncCheckpoint(CNode* pfrom)
{
    if (!CheckSignature())
        return false;

    LOCK(Checkpoints::cs_hashSyncCheckpoint);
    if (!mapBlockIndex.count(hashCheckpoint))
    {
        // We haven't received the checkpoint chain, keep the checkpoint as pending
        Checkpoints::hashPendingCheckpoint = hashCheckpoint;
        Checkpoints::checkpointMessagePending = *this;
        printf("ProcessSyncCheckpoint: pending for sync-checkpoint %s\n", hashCheckpoint.ToString().c_str());
        // Ask this guy to fill in what we're missing
        if (pfrom)
        {
            pfrom->PushGetBlocks(pindexBest, hashCheckpoint);
            //PushGetBlocks(pfrom, pindexBest, hashCheckpoint);
            // ask directly as well in case rejected earlier by duplicate
            // proof-of-stake because getblocks may not get it this time
            pfrom->AskFor(CInv(MSG_BLOCK, mapOrphanBlocks.count(hashCheckpoint)? WantedByOrphan(mapOrphanBlocks[hashCheckpoint]) : hashCheckpoint));
        }
        return false;
    }

    if (!Checkpoints::ValidateSyncCheckpoint(hashCheckpoint))
        return false;

    CTxDB txdb;
    CBlockIndex* pindexCheckpoint = mapBlockIndex[hashCheckpoint];
    if (!pindexCheckpoint->IsInMainChain())
    {
        // checkpoint chain received but not yet main chain
        CBlock block;
        if (!block.ReadFromDisk(pindexCheckpoint))
            return error("ProcessSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashCheckpoint.ToString().c_str());
        if (!block.SetBestChain(txdb, pindexCheckpoint))
        {
            Checkpoints::hashInvalidCheckpoint = hashCheckpoint;
            return error("ProcessSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashCheckpoint.ToString().c_str());
        }
    }

    if (!Checkpoints::WriteSyncCheckpoint(hashCheckpoint))
        return error("ProcessSyncCheckpoint(): failed to write sync checkpoint %s", hashCheckpoint.ToString().c_str());
    Checkpoints::checkpointMessage = *this;
    Checkpoints::hashPendingCheckpoint = 0;
    Checkpoints::checkpointMessagePending.SetNull();
    printf("ProcessSyncCheckpoint: sync-checkpoint at %s\n", hashCheckpoint.ToString().c_str());
    return true;
}
