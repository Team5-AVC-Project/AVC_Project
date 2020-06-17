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
int redLine();
struct motorSpeed moveRed();
void turnRobotRed(std::string type);
bool rightPathRed();
int leftSide();
bool redWall();


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
    bool mazeIsRed = false;
	while(1){
		takePicture();
		motorSpeed speedSet = {0, 0};
		if (!mazeIsRed){
			mazeIsRed = redMaze();
		}
		if (mazeIsRed){ // Prioritises red maze detection
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
} // Tests whether robot is following red walls or white lines

motorSpeed moveRed(){
	motorSpeed speedSet {20.0,20.0}; //default straight forward at 20.0 speed
	
	if (!(redWall())){ // Movement that doesn't require the detection of a wall in front
		if (leftSide() == 0){
			turnRobotRed("left");
		}
		if (leftSide() == 0 && rightPathRed()){
			while (!redWall()){
				setMotors(20.0, 20.0);
			}
			return {0, 0};
		}
		
		double dv = -0.66 * redLine(); //calculation for speed when following straights / soft corners
		speedSet.mLeft = 15.00 - dv;
		speedSet.mRight = 15.00 + dv;
		return speedSet;	
		
	} else { // Movement that does require the detection of a wall in front
		if (rightPathRed()){ // Turns right
			turnRobotRed("right");
		} else if(!(rightPathRed()) && (leftSide() > 0)){ // Detects dead end
			for (int i = 0; i<34; i++){ // Turns around
				setMotors(10, -10);
			}
			for (int i = 0; i<7; i++){ // Moves slightly forward
				setMotors(20, 20);
			}
		}
	}
	return speedSet;	
} //decides whether to go forward, left, right or turn around for red maze

int redLine(){
	int redPos = 0; // Pos number for where left wall is
	for (int i = 0; i < 75; i++){
		if (redPix(99, i) == 1){
			redPos = i;
		}
	}
	return (redPos - 10); 
} // Returns distance that wall is away from its desired position

bool redWall(){
	int redPos = 0;
	for (int i = 0; i<100; i++){
		if(redPix(i, 75) == 1){
			redPos = i;
		}
	}
	
	if (redPos > 60){ // Row 60 is when the front of robot is halfway in between walls to its side
		return true;
	} else {return false;}
} // Tests if a wall is infront of it

void turnRobotRed(std::string type){
	if(type=="left"){
		for (int i = 0; i<35; i++){ // Moves straight so that its inbetween walls again
			setMotors(20, 20);
		}
		for (int i = 0; i<17; i++){ // Turns 90 degrees
			setMotors(0, 20);
		}
		for (int i = 0; i<10; i++){ // Moves straight so that its inbetween walls again
			setMotors(20, 20);
		}
	}
	if(type=="right"){
		for (int i = 0; i<17; i++){ // Turns 90 degrees
			setMotors(20, 0);
		}
		for (int i = 0; i<5; i++){ // Moves straight so that its inbetween walls again
			setMotors(20, 20);
		}	
	}
} // Controls turning of robot

bool rightPathRed(){
	int rPixel = 0;
	for(int i = 130; i < 150; i++){
		rPixel += redPix(99, i);
	}
	if(rPixel == 0){
		return true;
	} else{return false;}	
} // checks if there is a pathway to the right

int leftSide(){
	int rPixels = 0;
	for (int i = 0; i<30; i++){
		rPixels += redPix(99, i);
	}
	return rPixels;
} // Checks if there is a path on the left side

int redPix(int r, int c){
	int rPix = get_pixel(cameraView, r, c, 0); // Gets red pixel value
	int gPix = get_pixel(cameraView, r, c, 1); // Gets green pixel value
	int bPix = get_pixel(cameraView, r, c, 2);; // Gets blue pixel value
	if(rPix == 255 && gPix < 5 && bPix < 5){ // Tests whether pixel is red
		return 1;
	} else {return 0;}
} // Tests to see if there is a red pixel located at the given coordinates
