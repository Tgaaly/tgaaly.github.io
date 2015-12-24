#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::endl;
using std::vector;


struct point{
	float x, y;
	point() : x(0), y(0){}
	point(float aX, float aY) : x(aX), y(aY) {}
};

typedef std::vector<point> point_container_t;

float computePolarAngle(point const& convex_pt, point const& candidate_pt){
	//move origin to convex_pt
	float candidate_x = candidate_pt.x - convex_pt.x;
	float candidate_y = candidate_pt.y - convex_pt.y;
	
	float angle = atan2(candidate_y,candidate_x);
    
	//incase the angle goes into the negative we always want to find the counterclockwise
	//angle from x-axis centered at the selected point
	if(angle < 0){
		return (2*M_PI) + angle;
	}
	else
	{
		return angle;
	}
}

//implementation of Jarvis's March ("Gift Wrapping")
point_container_t convexHull(const point_container_t& points){
    
	//declare structure to hold convex_points
	point_container_t convex_points;
    
	//checks
	size_t points_size = points.size();
	if(points_size <= 2){
		cout<<"points should consist of more than 2 points"<<endl;
		return convex_points;
	}
    
	//compute lowest point (min y-coord)
	point lowestPt(points.at(0).x, points.at(0).y);
	int lowestIndex = -1;
	for(size_t index=0; index < points_size ; index++){
		if(points.at(index).y < lowestPt.y)
		{
			lowestPt.x = points.at(index).x;
			lowestPt.y = points.at(index).y;
			lowestIndex = index;
		}
	}
    
	//add lowest point to convex hull
	convex_points.push_back(points.at(lowestIndex));
    
	//store remaining points (initially same as points) -> deep copy
	point_container_t remaining_points = points;
	
	//gift wrapping part loop while we have not reached the starting convex point again
	point convex_pt(lowestPt.x, lowestPt.y);
	bool flag_complete = false;
    float eps = 1e-5;
    
	while(!flag_complete){
		//compute polar angles of all points
		float minIndex = -1;
		float minAngle = 360;
		size_t remaining_size = remaining_points.size();
		
		for(size_t index=0; index < remaining_size ; index++){
			float polarAngle = computePolarAngle(convex_pt, remaining_points.at(index));
			if(polarAngle < minAngle && polarAngle!=0){//second condition is so that we dont compare a point with itself
				minAngle = polarAngle;
				minIndex = index;
			}
		}
        
		//better way to compare float numbers is to use relative error but div by zero, /0 -> infinity,  may arise and must be handled
		bool flagX = fabs(lowestPt.x - remaining_points.at(minIndex).x) < eps;
		bool flagY = fabs(lowestPt.y - remaining_points.at(minIndex).y) < eps;
		if(flagX && flagY){
			flag_complete = true;
			continue;
		}
		else{
			convex_points.push_back(remaining_points.at(minIndex));
			convex_pt.x = remaining_points.at(minIndex).x;
			convex_pt.y = remaining_points.at(minIndex).y;
			remaining_points.erase(remaining_points.begin()+minIndex);
		}
	}
    
	return convex_points;
}

int main(){
    
	//example set of points where the convex hull should be the 4 corners (a slightly deformed square)
	point_container_t points {point(1,1), point(1.1,-1), point(-1,1), point(-1.1,-1.1), point(0.75,0.5),
		point(-0.5,0.3), point(0.25,-0.8), point(0.1,-0.9)};
    
	cout<<"******************* points: *******************"<<endl;
	for(const point& pt : points){
    	cout << pt.x <<","<< pt.y << endl;
	}
    
	point_container_t convex_points = convexHull(points);//, convex_points, convex_points_indices);
    
	cout<<"******************* convex hull: *******************"<<endl;
	cout<<"found "<<convex_points.size()<<" points as the convex hull:"<<endl;
	for(auto it = convex_points.begin() ; it!=convex_points.end() ; it++){
		cout<<(*it).x<<", "<<(*it).y<<endl;
	}
}