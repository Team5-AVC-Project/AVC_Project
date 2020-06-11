#include "robot.hpp"

double errorAmount();
bool leftPath();

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
	  
	  if(leftPath()){
		vLeft = 20.00;
		vRight = 0.00;
	  }else{
		double dv = 0.20 * errorAmount(); //how much power to give wheels
		vLeft = 20.00 - dv;
		vRight = 20.00 + dv;
	  }
	  
	  std::cout<<std::endl;
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main

double errorAmount(){
	takePicture();
	  double whiteMiddle = 0.0; // middle of white line
	  int whiteNum = 0; //number of pixels in white line
	  double whitePos = 0.0; // sum of positions that are white  
	  
	  for (int i = 0; i < 150; i++){ // search along the halfway line for the white line
		  int pix = get_pixel(cameraView,80, i, 3);
		  int isWhite;
		  if(pix > 250){ 
			  isWhite = 1;
			  whitePos = whitePos + i; 
			  whiteNum = whiteNum + 1;
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
	  double error = (150/2) - whiteMiddle; // how far from middle white line is 
	  
	  return error;
} // finds white line, calculates amount of error then calculates how much to turn (dv)

bool leftPath(){
	int wPixel = 0;
		for(int i = 0; i < 100; i++){
			int pix = get_pixel(cameraView, 90.00, i, 3);
			wPixel;
			if(pix > 250){
				wPixel++;
			}
		}
		
		if(wPixel == 0){
			return true;
		}else{return false;}
}
