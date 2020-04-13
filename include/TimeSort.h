/*TimeSort.h
 *Class designed to first time-order raw data, and then based on a given coincidence window
 *sort the raw data into coincidence structures. Utilizes dictionary elements DPPChannel and
 *CoincEvent. Based on work by S. Balak, K. Macon, and E. Good from LSU. 
 *
 *Gordon M. Oct. 2019
 *
 *Refurbished and updated Jan 2020 GWM
 */
#ifndef TIME_SORT_H
#define TIME_SORT_H

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <TTreeReader.h>
#include <TTreeIndex.h>
#include "DataStructs.h"
#include "SabreMap.h"
#include "GainMatcher.h"

using namespace std;

class TimeSort {

  public:
    TimeSort(float windowSize, string mapfile, string gainfile);
    ~TimeSort();
    void Run(const char *infile_name, const char *outfile_name);

    /****** Data Counters *******/
    /*Use these for statistics on the event building*/
    int totalEvents;
    int completeFP;
    int completeFP_SABRE;
    int SABREorphans;
    int SABREorphans_noscint;
    int FPorphans;
    int FPorphans_partial;
    int FPorphans_noscint;
    int FPorphans_nogas;
    int FPextras;

  private:
    void Reset();
    void StartEvent();
    void ProcessEvent();

    float coincWindow;
    int illegalMap;
    bool illegalGains;
    vector<DPPChannel> hitList;
    DPPChannel hit;
    CoincEvent event;
    CoincEvent blank;
  
    ULong64_t startTime, previousHitTime;    
    unordered_map<int, sabrechan> smap;
    GainMatcher gains;

    /****** Focal Plane Global Channel Map ******/
    enum fpChMap {
      delayFL_id = 16*8+8,
      delayFR_id = 16*8+9,
      delayBL_id = 16*8+10,
      delayBR_id = 16*8+11,
      anodeF_id = 16*8+13,
      anodeB_id = 16*8+15,
      scintR_id = 16*8+0,
      scintL_id = 16*8+1,
      cath_id = 16*8+7
    };
    
};

#endif
