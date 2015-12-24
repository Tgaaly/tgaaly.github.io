#include <iostream>


using namespace std;

void printImage(int** img, int N){
    
	//check if image pointer is NULL
	if(img == NULL){
		return;
	}
    
	//check if any of the columns of the image are null (since its essentially an array of pointers)
	for(int i=0; i<N ; i++){
		if(img[i] == NULL){
			return;
		}
	}
    
	for(int i=0; i<N ; i++){
		for(int j=0; j<N ; j++){
			cout<<img[i][j]<<",";
		}
		cout<<endl;
	}
}

// ROTATE IMAGE BY 90 DEGREES
void do_rotateImageInplace(int** img, int N, int row, int col){
    
	//base condition --> return: do this by check if we need to go deeper into the "peels of the onion :)"
	if(row > N-row-1 || col < 0 || N==1)
	{
		return;
	}
    
	// Tmp usage --> to store row or column being rotated
	int* tmp = new int[N-row];
    
	//backup row
	for(int i=row; i<N-row ; i++){
		tmp[i]=img[i][col];
	}
    
	//copy row into col
	for(int i=N-row-1; i>=row ; i--){
		img[i][col] = img[row][i];
	}
    
	//swap tmp with end row
	for(int i=N-row-1 ; i>=row ; i-- ){
		int tmpVal = img[col][i];
		img[col][i] = tmp[N-i-1];
		tmp[N-i-1] = tmpVal;
	}
    
    
	// Swap end row into first col
	for(int i=N-(row)-2 ; i>=row ; i--){
		int tmpVal = img[i][row];
		img[i][row] = tmp[N-i-1];
		tmp[N-i-1]=tmpVal;
	}
    
	// Swap first column backup into first row
	for(int i=row+1; i<N-(row)-1 ; i++){
		img[row][i] = tmp[i];
	}
    
	delete[] tmp;
    
	do_rotateImageInplace(img, N, row+1, col-1);
}

void rotateImageInplace(int** img, int N){
    
    // Check if image pointer is NULL
	if(img == NULL){
		return;
	}
    
	// Check if any of the columns of the image are null (since its essentially an array of pointers)
	for(int i=0; i<N ; i++){
		if(img[i] == NULL){
			return;
		}
	}
    
	// If image is less than 2 in size
	if(N<2){
		return;
	}
    
	do_rotateImageInplace(img, N, 0, N-1);
}



int main(){
    
	//TEST CASES:
	int N = 5;
	int** img = new int*[N];
	int val = 0;
	for(int i=0; i<N ; i++){
		img[i] = new int[N] {val++,val++,val++,val++,val++};
	}
    
	cout<<"******* original image ******"<<endl;
	printImage(img, N);
    
	rotateImageInplace(img, N);
    
	cout<<"******* rotated image ******"<<endl;
	printImage(img, N);
    
	for(int i=0; i<N ; i++){
		delete img[i];
	}
	delete[] img;
    
}