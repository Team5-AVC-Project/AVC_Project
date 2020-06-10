#include "robot.hpp"



int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
	  takePicture();
	  double middle = 0.0;
	  int whiteNum = 0;
	  double error = 0.0;
	  for (int i = 0; i < 150; i++){
		  int pix = get_pixel(cameraView,99.99, i, 3);
		  int isWhite;
		  if(pix > 250){ 
			  isWhite = 1;
			  error = error + i; 
			  whiteNum = whiteNum + 1; // amount of white that occurs
		  }
		  else if (pix<=250){
			  isWhite=0; 
		  }
		  std::cout<<isWhite<<" ";
	  }
	  middle = error/whiteNum; //middle white line
	  double differenceErrorMiddle = (100/2) - middle; 
	  if (differenceErrorMiddle > 0){ //turns the robot to the right 
		  vLeft = 10.00;
		  vRight = 15.00;
	  }
	  else if (differenceErrorMiddle < 0){ //turns the robot to the left
		  vLeft = 15.00;
		  vRight = 10.00;
	  }
	  else if (differenceErrorMiddle == 0){ //moves straight
		  vLeft = 10.00;
		  vRight = 10.00;
	  }
	  else if (whiteNum == 0){ //moves robot straight when it's about to reach finish line
		  vLeft = 10.00;
		  vRight = 10.00;
	  }
	  
	  std::cout<<std::endl;
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
    } //while

} // main
