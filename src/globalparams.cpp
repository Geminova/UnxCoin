// Copyright 2016 UnxCoin Devs

#include "globalparams.h"

//////////////////////////////////////////////////////////////////////
///
/// Forks
///
//////////////////////////////////////////////////////////////////////
int const FEE_ADJUSTMENT_01_BLOCK = 64000;

// Tue Aug 22 06:00:00 2017 GMT (Mon Aug 22 23:00:00 PDT 2017)
unsigned int const PREMIUM_START_TIME = 1503381600;

// Tue Oct 3 05:00:00 2017 GMT (Mon Oct 2 22:00:00 PDT 2017)
unsigned int const FEE_FIX_01_TIME = 1507006800;

//////////////////////////////////////////////////////////////////////
///
/// Network Constants
///
//////////////////////////////////////////////////////////////////////

// network constants (used to be in netbase.cpp)

// random port number, not used much
unsigned short const TOR_PORT = 16255;

unsigned short const P2P_PORT = 38623;
unsigned short const P2P_PORT_TESTNET = 38625;

unsigned short const DEFAULT_PROXY = 9050;
unsigned short const DEFAULT_PROXY_TESTNET = 19050;

// rpc
unsigned short const RPC_PORT = 32683;
unsigned short const RPC_PORT_TESTNET = 32685;

// The message start string is designed to be unlikely to occur in normal data.
// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
// a large 4-byte int at any alignment.
unsigned char pchMessageStart[4] = { 0xfd, 0xdb, 0x9b, 0xdd };
unsigned char pchMessageStartTestnet[4] = { 0xe9, 0x9f, 0xdf, 0xfd };


//////////////////////////////////////////////////////////////////////
///
/// Minting Constants
///
//////////////////////////////////////////////////////////////////////
// target spacings
static const unsigned int nTargetSpacingPoS = 120;  // 2min
static const unsigned int nTargetSpacingPoW = 120;  // 2min
static const unsigned int nTargetSpacingPoWFirstDay = 6;  // 6sec
static const unsigned int nTargetSpacingPoSTestNet = 15;  // 15sec
static const unsigned int nTargetSpacingPoWTestNet = 15;  // 15sec
static const unsigned int nTargetSpacingPoWFirstDayTestNet = 6;  // 6sec
// block cutoffs
static const int LAST_FAIR_LAUNCH_BLOCK = 360;     // 60 * 6
static const int LAST_FIRST_DAY_BLOCK = 9015;      // 360 + (1440 * 6) + 15 [15 PRM]
static const int LAST_FAIR_LAUNCH_BLOCK_TESTNET = 36;     // 6 * 6
static const int LAST_FIRST_DAY_BLOCK_TESTNET = 180;      // 6 * 30


//////////////////////////////////////////////////////////////////////
///
/// PoS Constants
///
//////////////////////////////////////////////////////////////////////
#if PROOF_MODEL == PURE_POS
// must have a last PoW block if it is to be pure PoS
// optional overlap between PoW and PoS
// 2 min PoW and 2 min PoS
int LAST_POW_BLOCK = 181815;  // 1440 * 120 + 9015 = 172800 + 9015
int FIRST_POS_BLOCK = 9016;  // LAST_FIRST_DAY_BLOCK + 1
static const int LAST_POW_BLOCK_TESTNET = 36000;
static const int FIRST_POS_BLOCK_TESTNET = 181;
#elif PROOF_MODEL == MIXED_POW_POS
//
#endif  // PROOF_MODEL


//////////////////////////////////////////////////////////////////////
///
/// Money Constants
///
//////////////////////////////////////////////////////////////////////

// make sure these are consistent with nStakeMinAge
// 8 hr at 2 min block times
static const int nStakeMinConfirmations = 240;
// 10 min at 2 min block times
static const int nStakeMinConfirmationsTestnet = 5;

// avoid counting zeros
const int64_t BASE_COIN = 100000000;
const int64_t BASE_CENT = 1000000;

// different currencies (colored coins) have different money supplies
// fees are charged in the currency of the transaction
// const int BASE_FEE_EXPONENT = 5;

// some systems will want to multiply coinage by an interest rate
// unxcoin has a fixed and money supply dependent rewards
// const bool COINAGE_DEPENDENT_POS = false;

// for qualified addresses with currency as name
std::string ADDRESS_DELIMETER = "_";

// different currencies may have different divisibilities
//                               -     UNIH     PREM         DPST
const int64_t COIN[N_COLORS] = { 0, BASE_COIN,      1,  BASE_COIN };
//                               -     UNIH     PREM        DPST 
const int64_t CENT[N_COLORS] = { 0, BASE_CENT,     1,  BASE_CENT };

// related to max supply
//                            -      UNIH        PREM        DPST
//                            -  2,100,000,000     15   2,100,000,000
const int DIGITS[N_COLORS] = {0,            10,     2,             10 };


// related to divisibility in GUI
// should be consistent with behavior due to COLOR_UNITS
//                              -         UNIH      PREM        DPST
//                              -       0.0001         -      0.0001
const int DECIMALS[N_COLORS] = {0,           4,        0,          4 };


// this test is here to help with consistency
// but it could be that there could be a mix of coinage dependent and not
#if COINAGE_DEPENDENT_POS
// colored coins are generated based on relative preponderance
// these are in order of UNX_COLOR
// if a currency can't mint, then this value is not relevant
//                                           -  UNIH  PREM   DPST
const int64_t STAKE_MULTIPLIER[N_COLORS] = { 0,   1,     0,     0 };

#else
// If a currency can't mint, then this value is not relevant.
// These are somewhat like markers, and are
//    used for calculations in GetProofOfStakeReward().
// mint color (in order of UNX_COLOR)       -       UNIH     PREM   DPST
const int64_t BASE_POS_REWARD[N_COLORS] = { 0,   BASE_COIN,     0,     0 };
#endif

// IMPORTANT: make sure these values are in smallest divisible units
//                                                       UNIH       PREM                   DPST
//                                    -            2,100,000,000                     2,100,000,000
const int64_t MAX_MONEY[N_COLORS] = { 0,  BASE_COIN * 2100000000,    15,    BASE_COIN * 2100000000 };

/**********************************************************************
 *  A Note on Deposit and Withdrawal Fees
 **********************************************************************
 * Both fees are taken in UNIH. That is, the network takes the fee
 * in UNIH, but deposits and withdrawals are different in structure
 * so the fees come from different places.
 * Deposits - deposit fees are deducted from the DPT outputs. This
 * is possible because the OUTPUTS = INPUTS - FEES, where the
 * units of the terms do not matter. Example: imagine a deposit
 * of 100 UNIH with a fee of 1 UNIH added. In this case
 *     - OUTPUTS = 100 DPT
 *     - INPUTS = 101 UNIH
 *     - FEES = 1 UNIH
 * A miner would then be able to add 1 UNIH to his fees.
 * Withdrawals - withdrawal fees are deducted from the UNIH outputs.
 * Withdrawals are a little more complicated because of interest,
 * so there is another term:
 *    OUTPUTS = INPUTS + INTEREST - FEES
 * Let's imagine that an individual deposited the 100 UNIH, and it
 * collected 11 UNIH in interest, and the transaction cost 1 UNIH
 * in fees. Here
 *      - OUTPUTS = 110 UNIH
 *      - INPUTS = 100 DPT
 *      - INTEREST = 11 UNIH
 *      - FEES = 1 UNIH
 * A miner would be able to add 1 UNIH to his fees.
 * Of course with proof of stake, no miners claim fees, so the
 * network just eats them.
 **********************************************************************/                 

// Fees are complicated. Each currency can be sent with a fee payable in it's
// FEE_COLOR. Most of the times the FEE_COLOR is the transaction currency itself.
// For example, the fee currency for UNIH is UNIH. However, delegating a fee currency
// is necessary for atomic currencies with a low coin count. They would cease to
// be useful very quickly.
const int FEE_COLOR[N_COLORS] = { (int) UNX_COLOR_NONE,
                                  (int) UNX_COLOR_UNIH,     // UNIH
                                  (int) UNX_COLOR_UNIH,     // PREM
                                  (int) UNX_COLOR_UNIH };   // DPST


// MIN_TX_FEE, MIN_RELAY_TX_FEE, and OP_RET_FEE_PER_CHAR are in units of the **FEE_COLOR**

// $2 M cap -> ~$0.001 tx fee
// if cap grows to $20 B, then readjust
// min tx fees are *not* weighted by a priority multiplier
// these seem high, but are adjusted elsewhere
//                                           UNIH              PREM            DPST
const int64_t MIN_TX_FEE[N_COLORS] = { 0, BASE_CENT * 15,  BASE_CENT * 15, BASE_CENT * 15};


//                                                UNIH              PREM            DPST
const int64_t MIN_RELAY_TX_FEE[N_COLORS] = { 0, BASE_CENT * 15, BASE_CENT * 15, BASE_CENT * 15 };


// (0.015 per byte)
const int64_t COMMENT_FEE_PER_CHAR[N_COLORS] = { 0, (BASE_CENT * 15) / 1000,    // UNIH
                                                    (BASE_CENT * 15) / 1000,    // PREM
                                                    (BASE_CENT * 15) / 1000 };  // DPST


// op returns can be big, but they are expensive (0.015 per byte)
const int64_t OP_RET_FEE_PER_CHAR[N_COLORS] = { 0, (BASE_CENT * 23) / 1000,     // UNIH
                                                   (BASE_CENT * 23) / 1000,     // PREM
                                                   (BASE_CENT * 23) / 1000 };   // DPST


// Can the currency be transferred?
// Some currencies should not be transferrable because their use is restricted
// or depends on tokenized privileges. For example DPT can only be interconverted
// with UNIH, and relies on PREM for conversion from UNIH to DPT.
const bool TRANSFERABLE[N_COLORS] = { false, true, true, false };

// Can the currency be recovered by fee scavenging?
// DPT is not transferrable and is not a fee delegate. Therefore, there is no
// opportunity to lose it such that it could then be scavenged.
// Withdrawal fees may not be claimed, but these are taken in UHIH, which
// is scavengable.
//                                     -    UNIH   PREM    DPT
const bool SCAVENGABLE[N_COLORS] = { false, true, false, false };


// only used in GUI
//                                          -     UNIH           PREM       DPST
const int64_t MIN_TXOUT_AMOUNT[N_COLORS] = {0, BASE_CENT / 100,     1,  BASE_CENT / 100 };


// user configurable
//                                          -     UNIH          PREM       DPST
const int64_t MIN_INPUT_VALUE[N_COLORS] = {0,  BASE_CENT / 100,    1,  BASE_CENT / 100 };


// combine threshold for creating coinstake
// if a currency can't stake, then this value is not relevant
// IMPORTANT: make sure these values are in smallest divisible units
//                                                  -         UNIH       PREM   DPST
const int64_t STAKE_COMBINE_THRESHOLD[N_COLORS] = { 0, BASE_COIN * 1000,    0,     0 };


// what does a given currency mint (see GetProofOfStakeReward)
// these are in order of UNX_COLOR
const int MINT_COLOR[N_COLORS] = { (int) UNX_COLOR_NONE,
                                   (int) UNX_COLOR_UNIH,    // UNIH
                                   (int) UNX_COLOR_NONE,    // PREM
                                   (int) UNX_COLOR_NONE };  // DPST

const char *COLOR_TICKER[N_COLORS] = { "<none>", "UNH", "PRM", "DPT" };
                   
const char *COLOR_NAME[N_COLORS] = { "<none>", "UnxCoin", "Premium", "UnxDeposit" };


// these must be unique, except color none (first) is 0 or 0, 0 etc.
// for thousands of currencies, initialize with a loop

// first dimension is indexed by ADDESS_VERSION_INDEX enum
// IMPORTANT: don't use aColorID directly, it gets copied to vector COLOR_ID
// Yes, fitting the deck into one byte is going to make for some ugly addresses.
const unsigned char aColorID[N_VERSIONS][N_COLORS][N_COLOR_BYTES] = {
                                                                  //      -    UNIH   PREM   DPST
        /* Main Net PUBKEY */                                          { {0}, {108}, {103}, {219} },
        /* Main Net SCRIPT */                                          { {0}, {  5}, {145}, {116} },
        /* Test Net PUBKEY */                                          { {0}, {189}, {182}, {238} },
        /* Test Net SCRIPT */                                          { {0}, {188}, { 39}, {202} } };


// COLOR_ID (vector version of 3D aColorID)
std::vector<std::vector<std::vector<unsigned char> > > COLOR_ID(
                       N_VERSIONS, std::vector<std::vector<unsigned char> >(
                            N_COLORS, std::vector<unsigned char>(N_COLOR_BYTES)));

// Think of PRIORITY_MULTIPLIER this way:
//              priority ~ multiplier[color] * value_in * confs
// where value_in is in smallest divisible units (e.g. bitcoin -> satoshi).
// Miners will have to adjust these or have them set dynamically
// from the exchange values.

// PRIORITY_MULTIPLIER also adjusts fee-based prioritization.
// PRIORITY_MULTIPLIER should take into account these differences:
//   - total coin counts of the currencies
//   - differences in exchange values
//   - differences in how COIN is defined for each currency
// TODO: make this adjustable by RPC and configurable in the init.
//                                                 UNIH                 PREM      DPST
const int64_t PRIORITY_MULTIPLIER[N_COLORS] = { 0,   1,    BASE_COIN * 100000000,    1 };


// their weights determine how readily they stake
// these are in order of UNX_COLOR
// IMPORTANT: make sure to take money supply into account right here, these are per coin
//                                        -        UNIH  PREM  DPST
const int64_t WEIGHT_MULTIPLIER[N_COLORS] = { 0,     1,     0,    0 };


// These are for the premine blocks.
// IMPORTANT: make sure these values are in smallest divisible units
//      the smallest divisble unit of UNIH is the integer 1, which is the same as an unitoshi
// There is no premine for this coin.
//                                     -             UNIH             PREM    DPST
//                                               210,000,000             1       0
const int64_t POW_SUBSIDY[N_COLORS] = {0,   BASE_COIN * 210000000,       1,      0};


// MAPS_COLOR_ID is to look up values in case there are many currencies
// has this structure: 
//      [ {version1_bytes_color1 : color1, version1_bytes_color2, ...},
//        {version2_bytes_color1 : color1, version2_bytes_color2, ...}, ... ]
std::vector<std::map <std::vector <unsigned char>, int > > MAPS_COLOR_ID;


//////////////////////////////////////////////////////////////////////
///
/// GUI Constants
///
//////////////////////////////////////////////////////////////////////

// The default currency for the gui-less client is NONE.
// These are default currencies for the gui client, where the user
//    will need to have an operational client without any configuration.
const int DEFAULT_COLOR = (int) UNX_COLOR_UNIH;
const int DEFAULT_STAKE_COLOR = (int) UNX_COLOR_UNIH;

// For the gui, how divisible is the currency?
// For example, BTC is 3 (BTC, mBTC, uBTC)
// UNIH gui is strangely simplified
//                                 -  UNIH  PREM   DPST
const int COLOR_UNITS[N_COLORS] = {0,   2,     1,     2 };


// The GUI can create overview stats for only a few (e.g. 3) currencies.
// These are the default ordering
const int aGuiOverviewColors[N_GUI_OVERVIEW_COLORS] = { UNX_COLOR_UNIH };

// A vector is used so that number of currencies may be dynamic.
std::vector<int> GUI_OVERVIEW_COLORS;


//////////////////////////////////////////////////////////////////////
///
/// Currency Methods
///
//////////////////////////////////////////////////////////////////////


bool GetColorFromTicker(const std::string &ticker, int &nColorIn)
{
    nColorIn = (int) UNX_COLOR_NONE;
    for (int nColor = 1; nColor < N_COLORS; ++nColor)
    {
           if (std::string(COLOR_TICKER[nColor]) == ticker)
           {
                 nColorIn = nColor;
                 return true;
           }
    }
    return false;
}

bool GetTickerFromColor(int nColor, std::string &ticker)
{
     if (nColor < 1 || nColor > N_COLORS)
     {
              ticker = COLOR_TICKER[UNX_COLOR_NONE];
              return false;
     }
     ticker = COLOR_TICKER[nColor];
     return true;
}

bool CheckColor(int nColor)
{
    return (nColor >= 1 && nColor < N_COLORS);
}

bool CanStake(int nColor)
{
    if (!CheckColor(nColor))
    {
        return false;
    }
    if (MINT_COLOR[nColor] == UNX_COLOR_NONE)
    {
        return false;
    }
    return true;
}



int GetStakeMinConfirmations(int nColor)
{
    if (!CanStake(nColor))
    {
       return std::numeric_limits<int>::max();
    }
    if (fTestNet)
    {
       return nStakeMinConfirmationsTestnet;
    }
    return nStakeMinConfirmations;
}

int IsTransferrable(int nColor)
{
    if (!CheckColor(nColor))
    {
        return false;
    }
    return TRANSFERABLE[nColor];
}

bool SplitQualifiedAddress(const std::string &qualAddress,
                              std::string &address, int &nColor, bool fDebug)
{

    // find the delimeter
    size_t x = qualAddress.find(ADDRESS_DELIMETER);
    if (x == std::string::npos)
    {
          if (fDebug)
          {
              printf("Unable to find ticker suffix for %s\n", qualAddress.c_str());
          }
          return false;
    }

    // make the ticker, check, set nColor
    std::string ticker = qualAddress.substr(x + ADDRESS_DELIMETER.size(),
                                                          qualAddress.size());
    if (!GetColorFromTicker(ticker, nColor))
    {
          if (fDebug)
          {
              printf("Ticker is not valid for %s\n", qualAddress.c_str());
          }
          return false;
    }

    // make the address
    address = qualAddress.substr(0, x);

    return true;
}

// add b58 compatible bytes of n to end of vch, little byte first
bool AppendColorBytes(int n, std::vector<unsigned char> &vch)
{
        if(!CheckColor(n))
        {
               return false;
        }
        while (n >= 256)
        {
            vch.push_back(n & 255);   //  fast % 256
            n = n >> 8;               //  fast / 256
        }
        vch.push_back(n);
        return true;
}



//////////////////////////////////////////////////////////////////////
///
/// Data Structures
///
//////////////////////////////////////////////////////////////////////

bool ValueMapAllPositive(const std::map<int, int64_t> &mapNet)
{
    if (mapNet.empty())
    {
       return false;
    }
    std::map<int, int64_t>::const_iterator itnet;
    for (itnet = mapNet.begin(); itnet != mapNet.end(); ++itnet)
    {
        if (itnet->second <= 0)
        {
            return false;
        }
    }
    return true;
}

bool ValueMapAllZero(const std::map<int, int64_t> &mapNet)
{
    std::map<int, int64_t>::const_iterator itnet;
    for (itnet = mapNet.begin(); itnet != mapNet.end(); ++itnet)
    {
        if (itnet->second != 0)
        {
            return false;
        }
    }
    return true;
}


// effectively mapCredit - mapDebit
void FillNets(const std::map<int, int64_t> &mapDebit,
              const std::map<int, int64_t> &mapCredit,
              std::map<int, int64_t> &mapNet)
{
    mapNet = mapCredit;
    std::map<int, int64_t>::iterator itnet;
    std::map<int, int64_t>::const_iterator itdeb;
    for (itnet = mapNet.begin(); itnet != mapNet.end(); ++itnet)
    {
        for (itdeb = mapDebit.begin(); itdeb != mapDebit.end(); ++itdeb)
        {
            if (itnet->first == itdeb->first)
            {
                itnet->second -= itdeb->second;
                break;
            }
        }
    }
    for (itdeb = mapDebit.begin(); itdeb != mapDebit.end(); ++itdeb)
    {
        itnet = mapNet.find(itdeb->first);
        if (itnet == mapNet.end())
        {
            mapNet[itdeb->first] = -itdeb->second;
        }
    }
}





//////////////////////////////////////////////////////////////////////
///
/// Minting
///
//////////////////////////////////////////////////////////////////////

int64_t GetTargetSpacing(int nHeight, bool fProofOfStake)
{
    static int nLastFirstDayBlock = GetLastFirstDayBlock();
    int64_t nTargetSpacing = nTargetSpacingPoS;
    if (fProofOfStake)
    {
        if (fTestNet)
        {
            nTargetSpacing = nTargetSpacingPoSTestNet;
        }
    }
    else
    {
        if (nHeight <= nLastFirstDayBlock)
        {
            nTargetSpacing = fTestNet ? nTargetSpacingPoWFirstDayTestNet : nTargetSpacingPoWFirstDay;
        }
        else
        {
            nTargetSpacing = fTestNet ? nTargetSpacingPoWTestNet : nTargetSpacingPoW;
        }
    }
    return nTargetSpacing;
}


int GetLastFairLaunchBlock()
{
    return fTestNet ? LAST_FAIR_LAUNCH_BLOCK_TESTNET : LAST_FAIR_LAUNCH_BLOCK;
}

int GetLastFirstDayBlock()
{
    return fTestNet ? LAST_FIRST_DAY_BLOCK_TESTNET : LAST_FIRST_DAY_BLOCK;
}    

int GetLastPoWBlock()
{
    return fTestNet ? LAST_POW_BLOCK_TESTNET : LAST_POW_BLOCK;
}

int GetFirstPoSBlock()
{
    return fTestNet ? FIRST_POS_BLOCK_TESTNET : FIRST_POS_BLOCK;
}

