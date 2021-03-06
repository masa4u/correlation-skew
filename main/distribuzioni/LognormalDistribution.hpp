#ifndef lognormaldistribution_hpp
#define lognormaldistribution_hpp



class LogNormalDistribution
{
	private:
		double tau;
		double m;
		double s;

	public:
		LogNormalDistribution(){};
		LogNormalDistribution(double tau, double m, double s);
		double pdf(double x) const;

		void setParams(double tau, double m, double s);

		double M1() const;
		double M2() const;
		double M3() const;
		double M4() const;
		double M5() const;


		static double M1(double tau, double m, double s);
		static double M2(double tau, double m, double s);
		static double M3(double tau, double m, double s);
		static double M4(double tau, double m, double s);
		static double M5(double tau, double m, double s);
		
		double getTau() const;

};

#endif
