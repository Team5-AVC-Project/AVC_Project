#include "robot.hpp"

// Misc. initialiser for Program
bool redMaze();
bool isFinished();

// Method initialiser for White Line Maze
double errorAmount();
bool leftPath();
bool rightPath();
struct motorSpeed moveWhite();
void turnRobot(std::string type);

// Method initialiser for Red Wall Maze
int redPix(int r, int c);
int errorAmountRed();
struct motorSpeed moveRed();
bool turnRed();
int redLeft();
int redRight();
bool whiteLine();
void turnRobotRed(std::string type);



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
		motorSpeed speedSet = {0, 0};
		
		if (redMaze()){ // Prioritises red maze detection
			while (whiteLine()){
				speedSet.mLeft = 30;
				speedSet.mRight = 30;
				setMotors(speedSet.mLeft, speedSet.mRight);
			} // Positions robot properly in red maze
			speedSet = moveRed(); // Switches maze detection algorithm to red walls
		} else {
			speedSet = moveWhite(); // Switches maze detection algorithm to white line
		}  
		setMotors(speedSet.mLeft, speedSet.mRight);
		usleep(10000);
	} //while

} // main

// TESTING FOR WHITE MAZE

// ----------------------------*****----------------------------
// ----------------------------*****----------------------------
// ----------------------------*****----------------------------


motorSpeed moveWhite(){
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
		  if(pix > 250){ 
			  whitePos += i; 
			  whiteNum++;
		  }
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
		for(int i = 0; i < 5; i++){
				setMotors(15.0, 25.0);
		}
	}
	if(type=="right"){
		for(int i = 0; i < 5; i++){
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
} // checks whether finish flag is in sight


// TESTING FOR RED MAZE

// ----------------------------*****----------------------------
// ----------------------------*****----------------------------
// ----------------------------*****----------------------------

bool redMaze(){
	int redPixels = 0;
	int whitePixels = 0;
	
	for (int c=0; c < 150; c++){ // Column
		if (c <= 10 || c >= 140){
			redPixels += redPix(90, c);
		} else if(c < 140){
			int wPix = get_pixel(cameraView, 90, c, 3);
			if(wPix > 250){
				whitePixels++;
			}
		}
	}
	
	if (redPixels > 1 && whitePixels == 0){
		return true;
	} else {
		return false;
	}
}

motorSpeed moveRed(){
	motorSpeed speedSet {20.0,20.0}; //default straight forward at 20.0 speed
	
	if(isFinished()){return speedSet;}// if finish flag reached, continue straight
	
	if(turnRed() && (redLeft() > 0) && (redRight() > 0)){ // if dead end, turn around
		std::cout<<"turn around"<<std::endl;
		for (int i = 0; i<34; i++){
			setMotors(0, 20);
		}
	}
	
	if (redLeft() == 0 && redRight() == 0){ // If line is lost continue till wall is hit
		while(!(turnRed())){
			takePicture();
			setMotors(20, 20);
		}
	} else if(redLeft() == 0){ // turn left if left path is available
		turnRobotRed("left");
	} else if(redRight() == 0){ // if right path is available, turn right
		turnRobotRed("right");
	}
	
	double dv = -0.02 * errorAmountRed(); //calculation for speed when following straights / soft corners
	speedSet.mLeft = 20.00 - dv;
	speedSet.mRight = 20.00 + dv;
	
	return speedSet;	
		
} //decides whether to go forward, left, right or turn around for red maze

int errorAmountRed(){
	int redL = redLeft();
	int redR = redRight();
	int sideDiff = 0;
	
	if (redL == 0 || redR ==0){
		return 0;
	}
	sideDiff = redL - redR;
	return sideDiff;
} // Returns the amount of red pixels left side has more than red

int redLeft(){
	int redLeft = 0;
	for (int c = 0; c<75; c++){
			redLeft += redPix(90, c);
	}
	return redLeft;
} // Returns the amount of red pixels on the left of robot

int redRight(){
	int redRight = 0;
	for (int c = 75; c<150; c++){
		redRight += redPix(90, c);
	}
	return redRight;
} // Returns the amount of red pixels on the right of robot

bool turnRed(){
	int rPixel = 0;
	for (int i = 0; i<150; i++){
		if(redPix(60, i)){
			rPixel++;
		}
	}
	if (rPixel>75){
		return true;
	} else {return false;}
} // Tests if a wall is infront of it

bool whiteLine(){
	int wPix = 0;
	for (int i = 50; i < 100; i++){
		int wPix = get_pixel(cameraView, 99, i, 3);
		if(wPix > 250){
			wPix++;
		}
	}
	if (wPix > 0){
		return true;
	} else{return false;}
} // Tells the robot to position itself after line is gone

void turnRobotRed(std::string type){
	if(type=="left"){
		while(!(turnRed())){ // Moves straight till wall is found so that robot is roughly halfway between walls when turning
			takePicture();
			setMotors(20, 20);
		}
		for (int i = 0; i<17; i++){ // Turns 90 degrees
			setMotors(0, 20);
		}
		for (int i = 0; i<5; i++){ // Moves straight so that its inbetween walls again
			setMotors(20, 20);
		}
	}
	if(type=="right"){
		while(!(turnRed())){ // Moves straight till wall is found so that robot is roughly halfway between walls when turning
			takePicture();
			setMotors(20, 20);
		}
		for (int i = 0; i<17; i++){ // Turns 90 degrees
			setMotors(20, 0);
		}
		for (int i = 0; i<5; i++){ // Moves straight so that its inbetween walls again
			setMotors(20, 20);
		}	
	}
} // Controls turning of robot

int redPix(int r, int c){
	int rPix = get_pixel(cameraView, r, c, 0); // Gets red pixel value
	int gPix = get_pixel(cameraView, r, c, 1); // Gets green pixel value
	int bPix = get_pixel(cameraView, r, c, 2);; // Gets blue pixel value
	if(rPix == 255 && gPix < 5 && bPix < 5){ // Tests whether pixel is red
		return 1;
	} else {return 0;}
}


	

