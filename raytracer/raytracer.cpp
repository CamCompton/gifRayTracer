
#include <iostream>

#include <vector>
#include <cstdint>
#include "math.h"
#include "gif.h"

#include "color.h"
#include "vec3.h"
#include "shape.h"
#include "ray.h"
#include "triangle.h"
#include "square.h"
using namespace std;

#define PI 3.14159265

#define IMG_HEIGHT ((int)256)
#define IMG_WIDTH ((int)256)
#define MAX_BOUNCES 30
#define EDGE_WIDTH 2

#define Y_PAN_START 100
#define Y_PAN_END 100

#define NUM_ROTATIONS ((double).25)

#define FILE_NAME "db232.gif"
#define NUM_FRAMES 60 //Must be >= 2
#define GIF_DELAY 1

#define LOOP_GIF  //Comment out to disable loop

#define MAX_OBJ_DIST 999


//recursive ray trace function
color trace_ray(ray r, vector<Shape*> objs, int bounces) {

	double prec = .000001;
	if (bounces > MAX_BOUNCES) {
		return color(0, 0, 0);
	}

	double closest_obj_dist =  999;
	point3 closest_p = point3();
	point3 inter_p;
	int closest_obj_ind = -1;
	double t;

	//find the closest object that the ray intersects
	for (int i = 0; i < objs.size(); i++) {
		t = objs[i]->ray_to_obj_dist(r);

		if (prec < t && t < closest_obj_dist) {
			inter_p = r.at(t);

			if (objs[i]->contains_point(inter_p)) {
				closest_obj_dist = t;
				closest_obj_ind = i;
				closest_p = inter_p;
			}
		}
	}

	t = closest_obj_dist;
	//Return black if nothing is hit
	if (t >= MAX_OBJ_DIST || closest_obj_ind == -1) {
		return color(0, 0, 0);
	}
	
	inter_p = closest_p;
	//return a line color if the ray hits the edge of a plane.  Rays that have bounced more will return a dimmer color
	if (objs[closest_obj_ind]->min_dist_point_to_edge(inter_p) < EDGE_WIDTH) {
		return (objs[closest_obj_ind]->col() * pow(.90, bounces));
	}

	//continue ray in same direction if it has not yet bounced off an edge
	if (bounces == 0) {		
		return trace_ray(ray(inter_p, r.vec), objs, bounces + 1);
	}

	//else, bounce ray and recuse
	else {
		return trace_ray(ray(inter_p, objs[closest_obj_ind]->reflected_ray(r)), objs, bounces + 1);
	}
}


int main()
{
	uint8_t* gif_data_p;

	#ifdef LOOP_GIF
		vector<uint8_t*> gif_frames;
	#endif 
	
	auto fileName = FILE_NAME;
	int delay = GIF_DELAY;
	GifWriter g;
	GifBegin(&g, fileName, IMG_WIDTH, IMG_HEIGHT, delay);

	double img_ratio = 100 / (double)IMG_HEIGHT;

	double y_start = Y_PAN_START;
	double y_end = Y_PAN_END;
	double nr = NUM_ROTATIONS;

	double ystep = -(y_start - y_end) / (NUM_FRAMES - 1);
	double dstep = (nr * 360.0) / (NUM_FRAMES - 1);
	int f = 0;


	double y_vp_off = y_start;
	double deg = 45;
	for (int f = 0; f < NUM_FRAMES; f++) {
		
		std::cout << "Frame " << f + 1 << " of " << NUM_FRAMES << std::endl;
		gif_data_p = (uint8_t*)malloc(sizeof(uint8_t) * ((IMG_HEIGHT * IMG_WIDTH) * 4));
		vector<Shape*> objs;

		//Calculate cordinate offsets for rotation of square / square pyramid
		double xo1 =  (100.0 * sqrt(2.0)/2.0  * cos(deg * PI / 180));
		double xo2 =  (100.0 * sqrt(2.0) / 2.0 * cos((deg + 90) * PI / 180));
		double xo3 =  (100.0 * sqrt(2.0) / 2.0 * cos((deg + 180) * PI / 180));
		double xo4 =  (100.0 * sqrt(2.0) / 2.0 * cos((deg + 270) * PI / 180));

		double yo = 0;

		double zo1 = 150 + (100.0 * sqrt(2.0)/2.0 * sin(deg * PI / 180));
		double zo2 = 150 + (100.0 * sqrt(2.0) / 2.0 * sin((deg + 90) * PI / 180));
		double zo3 = 150 + (100.0 * sqrt(2.0) / 2.0 * sin((deg + 180) * PI / 180));
		double zo4 = 150 + (100.0 * sqrt(2.0) / 2.0 * sin((deg + 270) * PI / 180));

		//Square base Pyramid
		//Add sides to object vector
		objs.push_back(&Square(point3( xo1, 0 + yo, zo1),		point3(xo2, 0 + yo,  zo2),		point3(xo3, 0 + yo, zo3), point3( xo4, 0 + yo,  zo4), color(0, 20, 255 )));
		objs.push_back(&Triangle(point3( xo1, 0 + yo, zo1),		point3( xo2, 0 + yo, zo2),		point3(0 , sqrt(2.0)*50.0 + yo, 150 ),	color(225, 20, 0)));
		objs.push_back(&Triangle(point3( xo1, 0 + yo, zo1),		point3( xo4, 0 + yo, zo4),		point3(0 , sqrt(2.0) * 50.0 + yo, 150 ),	color(0, 225, 255)));
		objs.push_back(&Triangle(point3( xo4, 0 + yo, zo4),		point3( xo3, 0 + yo, zo3),		point3(0 , sqrt(2.0) * 50.0 + yo, 150 ),	color(0, 225, 5)));
		objs.push_back(&Triangle(point3( xo3, 0 + yo, zo3),		point3( xo2, 0 + yo, zo2),		point3(0 , sqrt(2.0) * 50.0 + yo, 150 ),	color(225, 20, 0)));


		point3 view_point = point3(0, y_vp_off, 0);

		for (int j = IMG_HEIGHT ; j > 0; j--) {
			for (int i = 0; i < IMG_WIDTH; i++) {
				vec3 rayp = point3((((double)i) * img_ratio) - 50, (((double)j) * img_ratio) - 45 + (y_vp_off*7/20), 90);
				ray r = ray(view_point, points_to_vector(view_point, rayp));
				color c = trace_ray(r, objs, 0);
				
				write_c(&gif_data_p[ ((IMG_HEIGHT - j) * (IMG_WIDTH * 4)) + ((i) * 4) ], c);
			}

		}
		GifWriteFrame(&g, gif_data_p, IMG_WIDTH, IMG_HEIGHT, delay);

		#ifdef LOOP_GIF
		gif_frames.push_back(gif_data_p);
		#endif 

		#ifndef LOOP_GIF
		free(gif_data_p);
		#endif 

		y_vp_off += ystep;
		deg += dstep;
	}
	#ifdef LOOP_GIF
	while (gif_frames.size() > 0) {
		gif_data_p = gif_frames.back();
		gif_frames.pop_back();
		GifWriteFrame(&g, gif_data_p , IMG_WIDTH, IMG_HEIGHT, delay);
		free(gif_data_p);
		}
	#endif 


	GifEnd(&g);
	

	return 0;
}
