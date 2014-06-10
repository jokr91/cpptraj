#ifndef TRAJIN_ENSEMBLE_H
#define TRAJIN_ENSEMBLE_H
#include "Trajin.h"
#include "ReplicaInfo.h"
/// Class for reading in single file ensemble trajectories.
class Trajin_Ensemble : public Trajin {
  public:
    Trajin_Ensemble();
    ~Trajin_Ensemble();
    // ----- Inherited Functions -----------------
    int SetupTrajRead(std::string const&, ArgList&, Topology*);
    int ReadTrajFrame(int, Frame&) {return 1;}
    int BeginTraj(bool);
    void EndTraj();
    void PrintInfo(int) const;
    bool HasVelocity() const;
    ReplicaDimArray const& TrajReplicaDimInfo() const { return trajRepDimInfo_; }
    int EnsembleSize() const { return ensembleSize_; }
    // NOTE: The following are currently for testing Trajin_Ensemble
    void EnsembleInfo() const;
    int EnsembleSetup(FrameArray&, FramePtrArray&);
    int ReadEnsemble(int, FrameArray&, FramePtrArray&);
    bool BadEnsemble() const { return badEnsemble_; }
    // -------------------------------------------
  private:
    typedef Frame::RemdIdxType RemdIdxType;
    ReplicaInfo::TargetType targetType_;
    TrajectoryIO* eio_;
    bool trajIsOpen_;
    bool badEnsemble_;
    int ensembleSize_;
    ReplicaDimArray trajRepDimInfo_;
    ReplicaMap<double> TemperatureMap_;
    ReplicaMap<RemdIdxType> IndicesMap_;
#   ifdef MPI
    RemdIdxType frameidx_;    ///< Hold position of each frame in ensemble.
#   endif 
};
#endif
