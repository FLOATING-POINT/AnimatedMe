#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxTextSuite.h"

class kinectSkelAniMesh{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void saveMeshPoints();
		void readMeshPoints();
		void resetPoints();

		void createTriangles();
		void createMesh();

		void createRadialPnts();
		void moveRadialPnts(int skelPntID);

		void setLiveSkelPoints(vector<ofVec3f> pnts);
		void updateSkelPoints();

		void setImg(ofImage newimg);

        bool                        doDraw;
		ofRectangle                 skelBoundingBox;

		float                       skelOriginX, skelOriginY;
		float                       skelDiffX, skelDiffY;

		int                         pntMode;
		ofImage                     img;

		vector<ofVec3f>             liveSkelPnts;
		vector<ofVec3f>             meshPointsAdded;

		int                         nPntsSkel;
		vector<ofVec3f>             meshSkelPnts;


		int                         nPntsPerSkelPnt;
		vector< vector<ofVec3f> >   meshRadialPnts;
		int                         skelPntRadius;

		vector< vector<int> >       meshVertexPntsForSkelPnts;

		float                       meshW, meshH;
		int                         offsetX, offsetY;
		int                         meshOffsetX, meshOffsetY;

		bool                        isDragging;
		int                         dragPntId;
		vector<int>                 dragVertexPntIds;

		ofxDelaunay                 triangulator;

		bool                        drawMeshWireframes;

		ofMesh                      mesh;
		ofVboMesh                   vboMesh;
		ofImage                     imgMesh;

};
