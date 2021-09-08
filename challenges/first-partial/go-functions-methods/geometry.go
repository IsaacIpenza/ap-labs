// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
package main

import (
	"math"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

// --- point --------------------------------------------------
type Point struct{ x, y float64 }

//Getters
func (p Point) X() float64 {
	return p.x
}
func (p Point) Y() float64 {
	return p.y
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X() - p.X() , q.Y() -p.Y())
}

// --- path ---------------------------------------------------
// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			dist := path[i-1].Distance(path[i])
			sum += dist
			fmt.Printf("%.2f + ", dist)
		}
	}

	dist:= path[len(path) - 1].Distance(path[0])
	sum += dist
	fmt.Printf("%.2f = %.2f \n", dist, sum)
	return sum
}

// --- line segments intersection -> Helpers ------------------
func onSegment(p, q, r Point) bool{
    if q.X() <= math.Max(p.X(), r.X()) && q.X() >= math.Min(p.X(), r.X()) && q.Y() <= math.Max(p.Y(), r.Y()) && q.Y() >= math.Min(p.Y(), r.Y()) {
       return true
	}
    return false
}

func orientation(p, q, r Point) int{
    
	val := (q.Y() - p.Y()) * (r.X() - q.X()) - (q.X() - p.X()) * (r.Y() - q.Y())
 
    if val == 0 {
		return 0  // colinear
	}
    
	if val > 0 { // clock or counterclock wise
		return 1
	} else {
		return 2 
	}
}

// --- Intersection -------------------------------------------
func doIntersect(p1, q1, p2, q2 Point) bool{

    o1 := orientation(p1, q1, p2)
    o2 := orientation(p1, q1, q2)
    o3 := orientation(p2, q2, p1)
    o4 := orientation(p2, q2, q1)
 
    // General case
    if o1 != o2 && o3 != o4 {
        return true
	}
    // Special Cases
    if o1 == 0 && onSegment(p1, p2, q1) {
		return true
	}
	if o2 == 0 && onSegment(p1, q2, q1) {
		return true
	}
	if o3 == 0 && onSegment(p2, p1, q2) {
		return true
	}
	if o4 == 0 && onSegment(p2, q1, q2) { 
		return true
	}
	
	return false
}

// --- Generate Figure ----------------------------------------
func generateFigure (sides int) Path {
	figure := make(Path, sides)
	rand.Seed(time.Now().UnixNano())

	for i := range figure {
				
		if i > 2 {
			flag := true
			
			for flag {
				
				figure[i].x = -100 + rand.Float64() * (200)
				figure[i].y = -100 + rand.Float64() * (200)

				flag = false
				for j := 0; j < i - 2 ; j++ {
					if doIntersect(figure[i], figure[i-1], figure[j], figure[j+1]) {
						flag = true
						break
						
					}	
				}

				if flag == false {
					for k := 1; k < i - 1; k++ {
						if doIntersect(figure[0], figure[i], figure[k], figure[k+1]) {
							flag = true
							break
						}
					}
				}
			}	

		} else {
			
			figure[i].x = -100 + rand.Float64() * (200)
			figure[i].y = -100 + rand.Float64() * (200)
		}

		fmt.Printf(" - (%.2f,%.2f)\n",figure[i].X(), figure[i].Y())
	}
	return figure
}

// --- main program -------------------------------------------
func main() {

	if len(os.Args) < 2 {
		fmt.Println("Invalid number of arguments")
		return
	}

	sides, err := strconv.Atoi(os.Args[1])

	if err != nil {
		fmt.Println("Invalid argument type")
		return
	}

	if sides < 3 {
		fmt.Println("Number of sides is to small")
		return
	}

	fmt.Printf(" - Generating a [%d] sides figure\n", sides)
	fmt.Println("- Figure's vertices")
	figure := generateFigure(sides)
	fmt.Println(" - Figure's Perimeter")
	figure.Distance()

}
