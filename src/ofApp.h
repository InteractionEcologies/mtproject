#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxBlobTracker.h"
#include "ofxFidMain.h"
//#include "ofxSyphon.h"
#include "ofxNetwork.h"
#include "Trackers/finger.h"
#include "Trackers/marker.h"
#include "json/json.h"
#include <map>

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
    /**
     *  ==== Utils ====
     */
    // Draw Functions
    void drawCameraViews();
    void drawMarkers();
    void drawFingers();
    void drawCalibrationPoints();
    
    
    /**
     * ==== Image Processing ====
     */
    // --- Variables ---
    bool readyToDraw;
    bool recordBackground;
    bool matReady;
    ofxKinect kinect;
    ofImage irImage;
    ofImage avgImage;
    ofImage diffImage;
    ofImage fingerImage;
    ofImage fidImage;
    
    // --- Functions ---
    void KinectSetup();
    void ImageProcessing();
    void UpdateBackground(const cv::Mat& input, cv::Mat &avg);
    
    
    
    /** 
     *  ==== Blob Tracking ====
      */
    // --- Variables ---
    ofImage thresholdImage;
    int imageThreshold;
    int blobThreshold;
    ofxBlobTracker blobTracker;
    float fingerSizeThreshold;
    float fingerSizeLowerThreshold;
    std::map<int, YJ::Finger> fingerPoints;
    std::map<int, YJ::Finger> fingerPoints_cv;
    bool fingerDirty;
    
    // --- Functions ----
    // -- Listener --
    void blobAdded(ofxBlob &_blob);
    void blobMoved(ofxBlob &_blob);
    void blobDeleted(ofxBlob &_blob);
    // -- Others --
    cv::Point2f transformPoint(cv::Point2f pt);
    void updateBlobTracker();
    
    
    
    // Fiducial Tracking
    // --- Variables ---
    ofxFiducialTracker fidfinder;
//    std::vector<YJ::Marker> markers;
    std::map<int, YJ::Marker> markers;
    // --- Functions ---
    void updateFidMarker(); // Transform from camera view to projection view
    bool markerDirty;
    void markerAdded(YJ::Marker& marker);
    void markerMoved(YJ::Marker& marker);
    void markerDeleted(YJ::Marker& marker);
    
    
    
    
    
    
    // Camera Calibration
    bool calibrationMode;
    bool calibrationDone = false;
    bool pointsSet[4];
    int currentCalibrationPt = 0;
    cv::Point2f cameraPoints[4]; 
    cv::Point2f calibrationPoints[4]; 
    cv::Mat warpMat;
    cv::Point2f debugPoint;
    
    void setCalibrationPoint();
    
    
    
    // ofxSyphon
//    ofxSyphonServer mainOutputSyphonServer;
//    ofxSyphonClient mClient;
    
    // UDP connections
    int udpPort;
    ofxUDPManager udpConnection;
    void networkSetup(int poty);
    void sendMsg();
};
