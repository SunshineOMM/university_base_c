#pragma once



namespace Cpp {
	struct point {
	private:
		double _x;
		double _y;
	public:
		point();
		point(double x, double  y);

		void setX(double x);
		void setY(double y);
		double getX()const;
		double getY()const;
		void pointDefinition();
	};
}