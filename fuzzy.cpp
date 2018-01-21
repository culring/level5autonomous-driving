Fuzzy::Fuzzy()
{
	left = 0.0f;
	midLeft = 0.0f;
	midRight = 0.0f;
	right = 0.0f;
};
Fuzzy::~Fuzzy(){};

void Fuzzy::setInterval(float l, float ml, float mr, float r)
{
	left = l;
	midLeft = ml;
	midRight = mr;
	right = r;
}
/*
bool Fuzzy::isDotInInterval(float t)
{
	if((t>=left) && (t<=right))
		return true;
	else
		return false;
}
*/
float Fuzzy::getValue(float t)
{
	if(t <= left)
	   return 1.0f;
	else if(t < midLeft)
		return (midLeft - t)/(midLeft-left);
	else if(t <= midRight)
		return 0.0f;
	else if(t < right)
		return (t-midRight)/(right-midRight);
	else
		return 1.0f;
}


float dist;
float turnValue;
float rate = 5.0f;	// idk
Fuzzy fuzzySet;

fuzzySet.setInterval(-50.0f, 0.0f, 0.0f, 50.0f);

// in while

// dist = segMid - vehiclePos
turnValue = fuzzySet.getValue(dist) * rate;
/*
  if((dist < 0.0f) && (vehicle.turn < turnValue))
  	  vehicle.turnRight; 	// or left idk
  if((dist > 0.0f) && (vehicle.turn > -turnValue))
  	  vehicle.turnLeft;		// or right idk either
 */
