#include <opencv2\opencv.hpp>
#include <vector>
#include <Windows.h>



using namespace cv;
using namespace std;






void subimage(int xres, int yres, int imgsize, int shift, Mat image, Mat filter, Mat filter2, int (&rect)[3]) {


	
	double c1 = 1;
	Mat testimage = Mat(32,32,0);

	int xtmp=0;
	int ytmp = 0;

	double avg = 0.0;

	double val = { 0.0 };
	for (int xs1 = 0; xs1 < xres - imgsize; xs1+=shift) {

		for (int ys1 = 0; ys1 < yres - imgsize; ys1+=shift) {

			for (int x1 = 0; x1 < imgsize; x1++) {
				for (int y1 = 0; y1 < imgsize; y1++) {

					 val += (double)image.at<uchar>(y1+ys1, x1+xs1)/255.0 * (double)filter.at<uchar>(y1,x1)/255.0;
					 val -= ((double)image.at<uchar>(y1 + ys1, x1 + xs1) / 255.0 * (double)filter2.at<uchar>(y1, x1) / 255.0)*-0.3;

				}
			}

			val = val / ((imgsize * imgsize));
			
			if (val < c1) {
				c1 = val;
				xtmp = xs1;
				ytmp = ys1;
			}
			
			val = 0.0;
			avg += val;
		}
	}

	
	int tmp[] = { ytmp,xtmp };

	rect[0] = xtmp;
	rect[1] = ytmp;


}


int calcSum(double scale, Mat Filter, Mat Image ) {


	return -1;
}


int main(){
	
	
		double scale = 2.0;


		VideoCapture cap{ 0 };
		cap.set(3, 1280);
		cap.set(4, 720);

		int rect[] =  { 0,0,1 };

		if (!cap.isOpened()) {

			return -1;


		}



		Mat filter = imread("C:\\FILTER\\Kernal 1.png", 0);

		Mat filter2 = imread("C:\\FILTER\\kernal 2.png", 0);


		for (;;) {
			Mat frame;
			cap >> frame;
			Mat OUTPUT = frame;
			Mat grayscale;
			cvtColor(frame, frame, COLOR_BGR2GRAY);
	

			resize(frame, frame, Size(320,180));
			subimage(320,180,32,10, frame, filter, filter2,rect);
			rectangle(OUTPUT, Point(rect[0]*4 - 200, rect[1]*4 - 300), Point(rect[0]*4 + 200, rect[1]*4 + 300), (255,255,0),4  );
			resize(frame, frame, Size(frame.size().width / scale, frame.size().height / scale));

			vector<Rect> faces;
			flip(frame, frame, 0);
			imshow("Webcam Frame", OUTPUT);

			if (waitKey(30) >= 0) {
				break;
			}
		}


	return 1;
}


