//PROTECT GLOBALS WITH MUTEX!
//RACE CONDITION
/*
[h264 @ 0x205e2a0] reference picture missing during reorder
[h264 @ 0x205e2a0] Missing reference picture
objects count... 3
[h264 @ 0x205b7c0] mmco: unref short failure
objects count... 2
[h264 @ 0x205b7c0] mmco: unref short failure

*/
#include <sstream>
#include <string>
#include <iostream>
//#include <opencv2\highgui.h>
#include "opencv2/highgui/highgui.hpp"
//#include <opencv2\cv.h>
#include "opencv2/opencv.hpp"
#include <vector>
#include <tuple>
#include "Client.h"
#include "Controller.h"
#include "Commander.h"
#include <string>
#include <thread>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mutex>

using namespace std;
using namespace cv;
//using namespace ClientNamespace;

//initial min and max HSV filter values.
//these will be changed using trackbars

// 145 H value and 35 S value for pink only
// 21 H and 65 S and 165 V for pink and yellow

int H_MIN = 29;
int H_MAX = 256;
int S_MIN = 65;
int S_MAX = 256;
int V_MIN = 165;
int V_MAX = 256;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 50 * 50;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const std::string windowName = "Original Image";
const std::string windowName1 = "HSV Image";
const std::string windowName2 = "Thresholded Image";
const std::string windowName3 = "After Morphological Operations";
const std::string trackbarWindowName = "Trackbars";


void on_mouse(int e, int x, int y, int d, void *ptr)
{
	if (e == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
}

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed
}

string intToString(int number) {


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void createTrackbars() {
	//create window for trackbars


	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN %d", H_MIN);
	sprintf(TrackbarName, "H_MAX %d", H_MAX);
	sprintf(TrackbarName, "S_MIN %d", S_MIN);
	sprintf(TrackbarName, "S_MAX %d", S_MAX);
	sprintf(TrackbarName, "V_MIN %d", V_MIN);
	sprintf(TrackbarName, "V_MAX %d", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH),
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->
	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);


}
void drawObject(int x, int y, Mat &frame) {

	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

	//UPDATE:JUNE 18TH, 2013
	//added 'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

	//cout<<"draw x y "<<x<<" "<<y<<"\n";

	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	if (y - 25 > 0)
		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
	if (y + 25 < FRAME_HEIGHT)
		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
	if (x - 25 > 0)
		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
	if (x + 25 < FRAME_WIDTH)
		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

	//cout<<"endedDraw x y "<<x<<" "<<y<<"\n";
	putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
	//cout << "x,y: " << x << ", " << y;

}
void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}

vector<pair<float,float>> objects;
vector<pair<float,float>> oldObjects;
FicPoint enemyObject;

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed) {

	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();

		vector<pair<float,float> > foundCoordinates;
		//if number of objects greater than MAX_NUM_OBJECTS we have a noise filter
		if (numObjects < MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//if (area > MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
				if (area > MIN_OBJECT_AREA && area<MAX_OBJECT_AREA) {
					//cout<<"ENTERED WITH "<<index<<"\n";

					pair<float,float> found = make_pair(moment.m10 / area, moment.m01 / area);
					foundCoordinates.push_back(found);

				}


			}
			//if object is found it will be found in foundCoordinates so no check is needed

			for(int i = 0; i < foundCoordinates.size(); i++){
				pair<float,float> found = foundCoordinates[i];
				putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(found.first, found.second, cameraFeed);
			}
            if (objects.size() > 1) {
                enemyObject = FicPoint(objects[1].first, objects[1].second);
            }
            //alt: m.lock();
            oldObjects = objects;
			objects = foundCoordinates;
            //m.unlock();
		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}

FicPoint botLeft;
FicPoint botRight;
FicPoint topLeft;
FicPoint topRight;

bool hasDestination = false;
//thread mindThread;
bool forceStop = false;
mutex m;

void calculateCommands(){
    
	while(!forceStop){
        m.lock();
		printf("objects count... %d\n",objects.size());
        m.unlock();
		sleep(2);
	}
}

void exitHandler(int s){
	printf("Caught signal %d\n",s);
	forceStop = true;
	//mindThread.join();

	exit(1);

}

int main(int argc, char* argv[])
{

	Controller *controller = new Controller();
	Commander *cmd = new Commander();

	struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = exitHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

	//some boolean variables for different functionality within this
	//program
	bool trackObjects = true;
	bool useMorphOps = true;

	Point p;
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	//x and y values for the location of the object
	int x = 0, y = 0;
	//create slider bars for HSV filtering
	createTrackbars();
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open("rtmp://172.16.254.99/live/nimic");
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop

	bool pink = true;
	thread mindThread(calculateCommands);
	while (1) {


		//store image to matrix
		capture.read(cameraFeed);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
		//filter HSV image between values and store filtered image to
		//threshold matrix

		inRange(HSV, Scalar(H_MIN, H_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);

/* Trivial way to do it - one object on one frame
		if (pink){
			inRange(HSV, Scalar(144, 35, 0), Scalar(H_MAX, S_MAX, V_MAX), threshold);
			pink = false;
		}else{
			pink = true;
			inRange(HSV, Scalar(21, 65, 165), Scalar(H_MAX, S_MAX, V_MAX), threshold);
		}
*/
		//perform morphological operations on thresholded image to eliminate noise
		//and emphasize the filtered object(s)
		if (useMorphOps)
			morphOps(threshold);
		//pass in thresholded frame to our object tracking function
		//this function will return the x and y coordinates of the
		//filtered object
		if (trackObjects)
			trackFilteredObject(x, y, threshold, cameraFeed);

		//show frames
		imshow(windowName2, threshold);
		imshow(windowName, cameraFeed);
		//imshow(windowName1, HSV);
		setMouseCallback("Original Image", on_mouse, &p);
		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
/*
    //FSM
    if (objects.size() > 0) {
        if(!cmd->hasDirection()){
						cout<<"Get Direction \n";
            controller->send("f");
            if (oldObjects.size() > 0){
								cout<<"Has old objects: finding direction \n";
                cmd->findDirection(FicPoint(objects[0].first, objects[0].second), FicPoint(oldObjects[0].first, oldObjects[0].second));
            }
        }else{
            if (hasDestination){
								cout<<"Schimbare de locatie ----> Padis, pentru ca sunt ursi si aparent a fost un atac :)) \n";
                if(objects.size() > 0){
	                if (cmd->isInBoundingBox(botLeft,botRight, topLeft,topRight, FicPoint(objects[0].first, objects[0].second))){
	                    hasDestination = false;
											cout<<"Reached destination \n";
	                }
								}
            }else{

                string direction = cmd->getDirection();
                cmd->calcDirectionLine(topLeft, botLeft, topRight, botRight);
                cmd->getLineCenter();


                if (!cmd->fitsEquation(FicPoint(objects[0].first, objects[0].second), enemyObject)){
                    controller->send("l");
										cout<<"Rotating left \n";
                }else{
									cout<<"On trajectory! \n";
	                double destinationThresh = 10;
	                //Axele sunt cele din reprezentarea naturala
	                topLeft = FicPoint(enemyObject.getX() - destinationThresh, enemyObject.getY() - destinationThresh);
	                topRight = FicPoint(enemyObject.getX() + destinationThresh, enemyObject.getY() - destinationThresh);
	                botLeft = FicPoint(enemyObject.getX() - destinationThresh, enemyObject.getY() + destinationThresh);
	                botRight = FicPoint(enemyObject.getX() + destinationThresh, enemyObject.getY() + destinationThresh);
	                hasDestination = true;

	                controller->send("f");
								}
                //Survive/Attack -> get point to go, rotate until it satisfies "ecutia dreptei"

            }
        }
    }
*/
		waitKey(30);
	}
	forceStop = true;
	mindThread.join();

	return 0;
}
