/*
 * Vertex.h
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <boost/shared_ptr.hpp>
#include <vector>

namespace fp_core {

class Renderer;

/// Represents a 2D point.
struct point {
	float x;
	float y;

	/**
	 * Checks if point A comes before point B counter clockwise to center.
	 *
	 * For example:
	 * Suppose we have A and B as follows:
	 *
	 * |      * B
	 * |
	 * |    * A
	 * |__________
	 *
	 * In a counter clockwise position, where the center is the origin, A comes
	 * before B. The algorithm translates A and B to local space (given by
	 * center), converts them to polar coordinates and then compares the angles.
	 *
	 *
	 *
	 * @param a The first point
	 * @param b The second point
	 * @param center The center where the angle will be compared against
	 * @param r The renderer that will be used to calculate the point transformation
	 * @return
	 */
	static bool comesBeforeCC(point a, point b, point center, Renderer& r);

	/// Returns the min and max values of a vector of points
    /**
     * Returns a vector of points that represent the minimum and maximum point
     * coordinates. This information can be used to create a bounding box.
     * Format: [min, max]
     */
	static std::vector<point> boundaries(const std::vector<point>& points);
};

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------
/// One vertex of a primitive
/**
 * Stores both the vertex position in space, and the uv coordinates of that
 * particular vertex
 */
class Vertex {
public:
	Vertex(point p);
	Vertex(const Vertex& v);
	virtual ~Vertex();

	/// Returns all positions in a vector<point> format
	/**
	 * Goes through each vertex in the vertices vector and pushes its getPosition()
	 * into a new vector that will be returned.
	 *
	 * @param vertices
	 * @return
	 */
	static std::vector<point> positionPointVector(const std::vector<Vertex> vertices);

	// ------------------------------
	// Getters
	// ------------------------------
	point    getPosition() const;
    point    getUvmap() const;

    // ------------------------------
    // Setters
    // ------------------------------
    void setPosition(point position);
    void setUvmap   (point uvmap);

    Vertex& operator= (const Vertex& v);

private:
    void copy_from(const Vertex& v);

	point    mPosition;
	point    mUvmap;
};

typedef boost::shared_ptr<Vertex> VertexPtr;

} /* namespace fp_core */
#endif /* VERTEX_H_ */
