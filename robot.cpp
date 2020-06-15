#include "robot.hpp"

double speedVariable();
bool lineLoss();
bool flagReached();

int main(){
	int spin = 1; //stores how much the robot has spun
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    
    while(1){
	  takePicture();

      if(flagReached() == true){ //stops if the flag is reached
		vLeft = 0.00;
		vRight = 0.00;	
	  }
	  else if(lineLoss() == false){ //if line in sight continues straight
		vLeft = 20.00 - speedVariable();
		vRight = 20.00 + speedVariable();
	  }
	  else{ //if neither of the above true turns around
		if(spin <= 6 && spin > 0){
			vLeft = 20.00;
			vRight = 0.00;
			spin ++;
	    }
	    else if(spin > 6){
			vLeft = 0.00;
			vRight = 20.00;
			spin = 0;
		}
		else{
			vLeft = 0.00;
			vRight = 20.00;
			spin++;
		}
	  }
	  
	  std::cout<<std::endl;
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main

bool lineLoss(){
	int whitePix = 0;
		for(int x = 0; x < 100; x++){
			int pix = get_pixel(cameraView, 99.99, x, 3);
			whitePix;
			if(pix > 250){
				whitePix++;
			}
		}
		if(whitePix == 0){
			return true;
		}
		else{
			return false;
		}
}//If the white line is lost spins until locating it again

double speedVariable(){
	takePicture();
	  double whiteMiddle = 0.0; // middle of white line
	  int whiteNum = 0; //number of pixels in white line
	  double whitePos = 0.0; // sum of positions that are white  
	  
	  for (int i = 0; i < 150; i++){ // search along the halfway line for the white line
		  int pix = get_pixel(cameraView, 99.99, i, 3);
		  int isWhite;
		  if(pix > 250){ 
			  isWhite = 1;
			  whitePos = whitePos + i; 
			  whiteNum++;
		  }
		  else if (pix<=250){
			  isWhite=0; 
		  }
		 std::cout<<isWhite<<" ";
	  }
	  if(whiteNum==0){ // if white line is gone then continue straight
		return 0.0;
	  }else{
		whiteMiddle = whitePos/whiteNum; 
	  }
	  double dv = 0.20*((150/2) - whiteMiddle); // how far from middle white line is 	  
	  return dv; //Addition to speed to give the wheels
} // finds white line, calculates distance from middle then calculates how much to turn (dv)

bool flagReached(){
	int blackPix = 0;
	int currentPix;
	for(int x = 0; x < 100; x++){
		for(int y = 0; y < 150; y++){
			currentPix = get_pixel(cameraView, x, y, 3);
			if(currentPix < 10){
				blackPix++;
			}
		}
	}
	if(blackPix > 2500){
		return true;	
	}
	else{
		return false;
	}
}//Checks for a sum of black pixels on the screen and if theres enough returns the flag has been reached
