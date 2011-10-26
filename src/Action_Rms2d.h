#ifndef INC_ACTION_RMS2D_H
#define INC_ACTION_RMS2D_H
/// Class: Rms2d
/// Action to calculate the RMSD between two sets of frames.
#include "Action.h"
#include "TrajectoryFile.h"
#include "CoordList.h"
#include "TriangleMatrix.h"
class Rms2d: public Action {
    CoordList ReferenceCoords; // Hold coords from input frames.
    bool nofit;                // Do not perform rms fitting
    AtomMask RefMask;          // Reference atom mask
    AtomMask FrameMask;        // Target atom mask
    char *rmsdFile;            // Output filename
    DataSetList RmsData;       // 1 data set for each ref frame to each tgt frame
    TrajectoryFile *RefTraj;   // Reference trajectory, each frame used in turn
    AmberParm *RefParm;        // Reference trajectory Parm

    void Calc2drms(TriangleMatrix*);
    void CalcRmsToTraj();
  public:
    Rms2d();
    ~Rms2d();

    int init();
    int setup();
    int action();
    void print();
};
#endif
