#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

#define DEBUG ;

struct Segment {
  int start, end;
};

struct Affsegments {
  int numAffSegments, PointPos;
};

// Sorts in increasing order
void sort_segments(vector<Segment>& segments){
  int size = segments.size(); // equals input n
  vector<Segment> temparray(size);
	vector<int> indexarr(size);
  indexarr[0] = -1;

  // Get minimum
	for (int ex=0; ex<size; ex++){
		int min = 1e9 + 1;
		for (int i=0; i<size; i++){
				bool condition = true;
				for (int looper=1; looper < ex+1; looper++){
					condition = condition && (i != indexarr[ex-looper]);
				}
				if (condition && (segments[i].start < min)){
						min = segments[i].start;
						indexarr[ex] = i;
				}
		}
		temparray[ex] = segments[indexarr[ex]];
	}

  for(int i=0; i<size; i++){
    // Now order also for the end points
    int minend = temparray[i].end;
    int minendind = i;
    for(int swa=i+1; swa<size; ++swa){
        if (temparray[i].start != temparray[swa].start)
          break;
        if (temparray[swa].end < minend){
          minend = temparray[swa].end;
          minendind = swa;
        }
    }
    int tempend = temparray[i].end;
    temparray[i].end = temparray[minendind].end;
    temparray[minendind].end = tempend;

    segments[i] = temparray[i];
#ifdef DEBUG
    std::cout << segments[i].start << " " << segments[i].end  << std::endl;
#endif
  }
#ifdef DEBUG
    std::cout << "Finished sorting the segments!" << std::endl;
#endif
}

// Find number of affected segments for a given point
int findaff_segments(int pointpos, int segmentindex, vector<Segment> &segments, int* affectedsegments){
  int res = 0;
  for (int i=segmentindex; i<segments.size(); ++i){
    if (segments[i].start <= pointpos && segments[i].end >= pointpos && !affectedsegments[i]){
      res ++;
    }
  }
  return res;
}

// Find the maximum number of affected segments for a given scan and return the location where to put the point
int findmax_affsegments(vector<Affsegments>& affectedseggen){
  int max = 0;
  int maxindex;
  for (int i=0; i<affectedseggen.size(); ++i){
    if(affectedseggen[i].numAffSegments > max){
      max = affectedseggen[i].numAffSegments;
      maxindex = i;
    }
  }
  return affectedseggen[maxindex].PointPos;
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  int size = segments.size();
  int affected_segments[size] = {0};  // a '1' indicates the segment is already affected by a chosen point

  sort_segments(segments);

  for (int ev_seg = 0; ev_seg < size; ++ev_seg ){ //size
    if (!affected_segments[ev_seg]){
      if (segments[ev_seg].start == segments[ev_seg].end){
        points.push_back(segments[ev_seg].start);
        // Now determnine the affected segments so they are no longer considered
        for (int i=0; i < size; ++i){
          if (segments[i].start <= segments[ev_seg].start && segments[i].end >= segments[ev_seg].start )
            affected_segments[i] = 1;
        }
        continue;
      }
      vector<Affsegments> affectedseggen;  // vector to find out where two put the point so more segments are included
      for (int mapp = ev_seg + 1; mapp < size; ++mapp){
        if (segments[mapp].start <= segments[ev_seg].end ){
            // Find the number of affected segments for the current location
            Affsegments seg;
            seg.PointPos = segments[mapp].start;
            seg.numAffSegments = findaff_segments(seg.PointPos, ev_seg, segments, affected_segments); //mapp - ev_seg + 1;// HERE IS THE ERROR
            affectedseggen.push_back(seg);
        }
        else{
          if(mapp == ev_seg+1){
            Affsegments seg;
            seg.PointPos = segments[ev_seg].start;
            seg.numAffSegments = 1;//
            affectedseggen.push_back(seg);
          }
          break;
        }
      }
      if(ev_seg == size-1){ // If we reach the last segment and was still not reached by a point.
        Affsegments seg;
        seg.PointPos = segments[ev_seg].start;
        seg.numAffSegments = 1;//
        affectedseggen.push_back(seg);
      }
      // here find the maximum in affectedseg and chose that point and store it in points
      int pointcoor = findmax_affsegments(affectedseggen);
      points.push_back(pointcoor);
      // Now determnine the affected segments so they are no longer considered
      for (int i=0; i < size; ++i){
        if (segments[i].start <= pointcoor && segments[i].end >= pointcoor )
          affected_segments[i] = 1;
      }
      affectedseggen.clear();
    }
  }

  return points;
}

void test_solution1(){
  int n = 100;
  int start[] = {41,52,63,80,78,35,22,31,44,81,36,10,1,23,32,87,55,69,89,93,38,33,14,57,70,36,29,73,66,36,1,49,68,26,30,1,64,57,58,51,41,17,45,4,0,65,92,84,75,39,15,29,83,12,91,83,81,3,66,8,17,86,44,34,74,94,79,29,60,58,62,54,58,79,89,40,2,12,5,28,35,7,82,49,2,57,25,52,48,9,10,78,26,83,22,86,52,49,63,54};
  int end[] = {42,52,63,82,79,35,23,32,45,82,38,12,1,23,33,88,56,71,91,93,40,34,16,59,72,36,29,74,68,38,3,50,70,28,30,2,65,58,58,53,41,18,46,4,1,67,93,85,77,41,15,31,84,14,93,84,81,4,67,8,19,87,44,34,74,95,81,29,61,59,62,56,58,79,91,42,4,14,5,28,36,8,84,51,4,59,27,53,49,9,10,78,26,84,24,87,54,51,64,54};
  vector<Segment> segments(n);
  for (int i=0; i< 100; ++i){
    segments[i].start = start[i];
    segments[i].end = end[i];
  }

  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
  std::cout << std::endl;
}

void test_solution2(){
  int n = 10;
  //int start[] = {58,60,62,63,63};
  //int end[] = {58,61,62,63,64};
  //int start[] = {0,1,1,1,2,2,3};
  //int end[] = {1,1,3,2,4,4,4};
  //int start[] = {87,89,89,91,92,93,94};
  //int end[] = {88,91,91,93,93,93,95};
  int start[] = {34,35,35,36,36,36,38,39,40,41};
  int end[] = {34,35,36,38,36,38,40,41,41,42};
  vector<Segment> segments(n);
  for (int i=0; i< segments.size(); ++i){
    segments[i].start = start[i];
    segments[i].end = end[i];
  }

  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}

int main() {

#ifdef DEBUG
  test_solution1();
  test_solution2();
#else

  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }

  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
#endif
}
