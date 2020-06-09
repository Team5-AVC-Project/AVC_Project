#include "robot.hpp"



int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    //takePicture();
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
	  takePicture();
	  double error = 0.0;
	  double middle = 0.0;
	  int errorNum = 0;
	  double errorTotal = 0;
	  for (int i = 0; i < 150; i++){
		  int pix = get_pixel(cameraView, 50, i, 3);
		  int isWhite;
		  if(pix > 250){ 
			  isWhite = 1;
			  errorTotal = errorTotal + i;
			  errorNum = errorNum + 1;
			  error = i;
		  }
		  else if (pix<=250){
			  isWhite=0; 
		  }
		  std::cout<<isWhite<<" ";
	  }
	  middle = errorTotal/errorNum;
	  double turn = 0;
	  if (error > middle){
		  turn = error - middle;
		  vLeft = turn;
		  vRight = -turn; 
	  }
	  else if (error < middle){
		  turn = middle - error; 
		  vLeft = -turn;
		  vRight = turn;
	  }
	  else{
		  vLeft = 10;
		  vRight = 10;
	  }
	  
	  std::cout<<std::endl;
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
    } //while

} // main
