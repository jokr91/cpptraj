#ifndef INC_TRAJECTORYIO_H
#define INC_TRAJECTORYIO_H
#include "Topology.h" // Box
#include "FrameArray.h"
#include "FramePtrArray.h"
#include "CpptrajFile.h"
#include "ArgList.h"
#include "BaseIOtype.h"
// Class: TrajectoryIO
/// Abstract base class for performing trajectory reading and writing.
/** This is the generic interface for a trajectory format used by 
  * TrajectoryFile-derived classes.
  */
class TrajectoryIO : public BaseIOtype {
  public:
    TrajectoryIO() : debug_(0) {}
    virtual ~TrajectoryIO() {} // virtual since this class is inherited.
    // -----------===== Inherited functions =====-----------
    /// \return true if file format matches trajectory type.
    virtual bool ID_TrajFormat(CpptrajFile&) = 0;
    static const int TRAJIN_ERR = -1;
    static const int TRAJIN_UNK = -2;
    /// Set up trajectory IO for READ
    /** First arg is the trajectory name. Second arg is the Topology that
      * will be associated with this trajectory.
      * \return Number of frames in trajectory.
      * \return TRAJIN_ERR if an error occured during setup.
      * \return TRAJIN_UNK if the number of frames could not be determined.
      */
    virtual int setupTrajin(std::string const&, Topology*) = 0;
    /// Set up and open trajectory IO for WRITE/APPEND 
    /** Called on the first write call. Args are: 1) trajectory file name,
      * 2) Topology associated with this trajectory, 3) coordinate metadata
      * (velocities, temperatures, etc), 4) number of frames expected to be
      * written out, 5) whether trajectory should be appended to.
      * \return 0 on success, 1 on error.
      */
    virtual int setupTrajout(std::string const&,Topology*,CoordinateInfo const&,int,bool) = 0; 
    /// Open previously set-up input trajectory, prepare for IO.
    virtual int openTrajin() = 0;
    /// Read a frame from trajectory
    /** Given a frame number, read that frame.
      * \return 1 on error, 0 on success.
      */
    virtual int readFrame(int,Frame&) = 0;
    /// Read only velocity information from a trajectory. 
    virtual int readVelocity(int, Frame&) = 0;
    /// Write a frame to trajectory
    /** Write to output trajectory. This routine is called from
      * TrajectoryFile::WriteFrame with the current action set number, not the 
      * current output number, so it is up to the TrajectoryIO object to keep 
      * track of what frame it is writing. 
      */
    virtual int writeFrame(int,Frame const&) = 0;
    /// Close trajectory
    virtual void closeTraj() = 0; 
    /// Print information on what kind of trajectory this is.
    virtual void Info() = 0; 
    /// Process arguments relevant to writing trajectory (optional)
    /** Process any arguments from the arg list that have to do with 
      * setting the trajectory up for writing. Called before setupTrajout, so 
      * none of the arguments should be parm-related. It is desireable that any 
      * changes made to the TrajectoryIO object from within this function are
      * implemented as functions that can be called independently if need be 
      * (e.g. setting the write mode for PDB files).
      */
    virtual int processWriteArgs(ArgList&) = 0; 
    /// Process arguments relevant to reading trajectory (optional)
    virtual int processReadArgs(ArgList&) = 0;
    /// \return true if this IO is suitable for single file ensemble IO
    virtual bool CanProcessEnsemble() { return false; } // TODO: Pure virtual/make part of CoordinateInfo?
    /// Read frame array
    virtual int readArray(int, FrameArray&) { return 1; }
    /// Write frame array
    virtual int writeArray(int, FramePtrArray const&) { return 1; }
    // -----------------------------------------------------
    CoordinateInfo const& CoordInfo() const { return coordInfo_; }
    std::string const& Title()        const { return title_;     }

    void SetDebug(int dIn)                       { debug_ = dIn;     }
    void SetTitle(std::string const& tIn)        { title_ = tIn;     }
  protected:
    void SetCoordInfo(CoordinateInfo const& cIn) { coordInfo_ = cIn; }
    int debug_;               ///< Trajectory debug level.
  private:
    CoordinateInfo coordInfo_; ///< Metadata associated with coordinate Frame
    std::string title_;        ///< Set to trajectory title.
}; 
#endif
