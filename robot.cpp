#include "robot.hpp"

double errorAmount();
bool leftPath();
bool rightPath();
struct motorSpeed move();
void turnRobot(std::string type);
bool isFinished();

struct motorSpeed{
		double mLeft;
		double mRight;
}; // stores left and right motor speeds

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    
  while(1){
		takePicture();
		motorSpeed speedSet = move(); //struct containing left and right motor speed
		  
		setMotors(speedSet.mLeft, speedSet.mRight);
		std::cout<<" vLeft="<<speedSet.mLeft<<"  vRight="<<speedSet.mRight<<std::endl;
		usleep(10000);
	} //while

} // main

motorSpeed move(){
	motorSpeed speedSet {20.0,20.0}; //default straight forward at 20.0 speed
	
	if(isFinished()){return speedSet;}// if finish flag reached, continue straight
	if(errorAmount()==0 && !leftPath() && !rightPath()){ // if line is lost, turn around
		speedSet.mLeft = 10.00;
		speedSet.mRight = -10.00;
		return speedSet;
	}
	if(errorAmount()==0 && !leftPath() && rightPath()){ // turn right if theres no forward or left path
		turnRobot("right");
	}
	if(leftPath()){ // if left path is available, turn left
		turnRobot("left");
	}
	
	double dv = 0.20 * errorAmount(); //calculation for speed when following straights / soft corners
	speedSet.mLeft = 20.00 - dv;
	speedSet.mRight = 20.00 + dv;
	return speedSet;
} //decides whether to go forward, left, right or turn around

double errorAmount(){
	takePicture();
	  double whiteMiddle = 0.0; // middle of white line
	  int whiteNum = 0; //number of pixels in white line
	  double whitePos = 0.0; // sum of positions that are white  
	  
	  for (int i = 0; i < 150; i++){ // search along the halfway line for the white line
		  int pix = get_pixel(cameraView,90, i, 3);
		  int isWhite;
		  if(pix > 250){ 
			  isWhite = 1;
			  whitePos += i; 
			  whiteNum++;
		  }
		  else if (pix<=250){
			  isWhite=0; 
		  }
		 std::cout<<isWhite<<" ";
	  }
	  if(whiteNum==0){ // if white line is gone 
		return 0.0;
	  }else{
		whiteMiddle = whitePos/whiteNum; 
	  }
	  double error = (150/2) - whiteMiddle; // how far from middle white line is 
	  return error;
} // finds white line, calculates amount of error then calculates how much to turn (dv

bool leftPath(){
	int wPixel = 0;
	for(int i = 80; i < 100; i++){
		int pix = get_pixel(cameraView, i, 30, 3);
		//wPixel;
		if(pix > 250){
			wPixel++;
		}
	}
	if(wPixel > 0 && wPixel < 10){
		return true;
	}else{return false;}
} // checks if there is a pathway to the left

bool rightPath(){
	int wPixel = 0;
	for(int i = 80; i < 100; i++){
		int pix = get_pixel(cameraView, i, 120, 3);
		//wPixel;
		if(pix > 250){
			wPixel++;
		}
	}
	if(wPixel > 0 && wPixel < 10){
		return true;
	}else{return false;}	
} // checks if there is a pathway to the right

void turnRobot(std::string type){
	if(type=="left"){
		for(int i = 0; i < 30; i++){
				setMotors(15.0, 25.0);
		}
	}
	if(type=="right"){
		for(int i = 0; i < 30; i++){
			setMotors(25.0, 15.0);
		}
	}
} // turn robot either left or right (for 90 degree corners)

bool isFinished(){
	int bPixel = 0;
	int pix;
		for(int row = 1; row < 100; row++){
			for(int col = 1; col < 150; col++){
				pix = get_pixel(cameraView, row, col,3);
				bPixel;
				if(pix < 5){bPixel++;}
			}
		}
	if(bPixel > 1000){
		std::cout<<"FINISHED"<<std::endl;
		return true;
	}else{return false;}
} // checks whether finish flag is in site