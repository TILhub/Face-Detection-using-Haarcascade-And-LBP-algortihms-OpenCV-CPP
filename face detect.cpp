#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
/*
For using haarcascade just replace the face_cascade_name to haarcascade train data location 
*/



//"C:/Opencv3/install/etc/lbpcascades/lbpcascade_frontalcatface.xml"
String face_cascade_name ="C:/Opencv3/install/etc/lbpcascades/lbpcascade_frontalcatface.xml" ;//"C:/Opencv3/install/etc/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "C:/Opencv3/install/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
//C:/Opencv3/install/etc/haarcascades/lbpcascade_frontalface_alt.xml"/lbpcascade_frontalcatface.xml

void detectAndDisplay(Mat& frame, CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade);
int main()
{
	Mat frame, capture;
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	if (!face_cascade.load(face_cascade_name)) { cout<<"Error Loading "<<face_cascade_name<<endl; return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { cout << "Error Loading " << eyes_cascade_name << endl; return -1; };
	/*frame = imread("e:/test2.jpg");
	if (frame.empty()) {							//function to read from a single file
		cout<< "File Not Found\n";
		return -1;
	}*/
	VideoCapture vap(0);
	vap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vap.set(CV_CAP_PROP_FRAME_HEIGHT, 360);
	if (!vap.isOpened()) {
		cout << "Camera not Initialized\n";
			return -1;
	}
	while (1) {
		vap >> frame;
		detectAndDisplay(frame, face_cascade, eyes_cascade);			//to read from camera
		
	}
	return 0;
}
void detectAndDisplay(Mat& frame, CascadeClassifier& face_cascade, CascadeClassifier& eyes_cascade)
{

	vector<Rect> faces;
	Mat frame_gray;
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);		//just to optimize the image
	//can also split the image into BGR frames and then equalize the image and merge again for better results but is slower
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	for (int i = 0;i < faces.size();i++)
	{
		Point center(int(faces[i].x + faces[i].width*0.5), int(faces[i].y + faces[i].height*0.5));//to find center of face (used to draw ellipses)
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
		Mat faceROI = frame_gray(faces[i]);

		// un comment the below code to detect eyes also
	/*	std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, center, radius, Scalar(0, 255, 0), 4, 8, 0);
		}*/
	}
	imshow("Display", frame);
	waitKey(30);
}