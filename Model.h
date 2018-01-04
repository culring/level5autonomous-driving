#define TRACK_SIZE 16

class Model
{
public:
	Car *vehicle;
	Track *map;
	
	Model();
	~Model();
};


class Car
{
public:
	float x, y, dir;			// car's current position and direction it's facing
	
	Car();
	~Car();
};


class Track
{
public:
	Segment *segList;			// current track
	int k;
	
	Track();
	~Track();
	
	void Update(float posX, float posY, float faceDir, int segmentType, float rads);				// replace old segments with new ones
};


class Segment
{
public:
	float x, y, dir;
	int segType;
	
	float rad;					// turn degree (0 for straight segments)
	
	Segment();
	Segment(float posX, float posY, float faceDir, int segmentType, float rads);
	~Segment();
	
	void setSegment(float posX, float posY, float faceDir, int segmentType, float rads);
};