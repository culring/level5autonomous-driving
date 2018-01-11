#define TRACK_SIZE 16

class Car
{
public:
	float x, y, dir;			// car's current position and direction it's facing
	
	Car();
	~Car();
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

class Track
{
public:
	Segment *segList;			// current track
	int k;
	
	Track();
	~Track();
	
	void update(float posX, float posY, float faceDir, int segmentType, float rads);				// replace old segments with new ones
};

class Race
{
public:
	Car *vehicle;
	Track *map;

	Race();
	~Race();
};
