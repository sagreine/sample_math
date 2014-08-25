

#include <iostream>
#include <string>

using namespace std;

// tail recursive - one-time payment with annual interest rate for a # of years - what is it worth at the end?
double final_val (double value, double rate, unsigned int years)
{
	if (years == 0)
	{
		return value;
	}
	else 
	{    // the new value is equal to the old value * (1 + rate / 100). e.g., 100 * 1.04 == 104.
		return final_val(value * (1 + rate / 100), rate, --years);
	}
}

// iterative version of above
double final_val_iterative (double value, double rate, unsigned int years)
{
	int i;
	// for each year we are processing, multiply the running total by (1 + rate / 100);
	for (i = 0; i < years; i++)
	{
		value  = value * (1 + rate / 100);
	}
	return value;
}

// repeated payments - if you get a certain payment once a year, and annual interest on the total each year
//                     how much will you have at the end of n years? This is recursive
double final_val_R (double initial, double value, double rate, unsigned int years)
{
    if (years == 1)
	{
		// at the last year, return the value * (1 + rate / 100).
		//return value * (1 + rate / 100 // this is the same as below (this is a manual way to calculate a one time payment for one year)
		return final_val(value, rate, 1);
	}
	else
	{
		return final_val_R(initial, value * (1 + rate / 100) + initial, rate, --years);
	}
}


// recursive
double final_val_increment (double value, double rate, unsigned int years)
{
	if (years == 0)
	{
		return value;
	}
	else 
	{
		return (250 + final_val(value * (1 + rate / 100), rate, --years));
	}
}

double sum_needed_for_free (double rate_of_return, double cost_of_item)
{
   return cost_of_item * (1 / (rate_of_return / 100) );
}

int main()
{
	string menu_choice;
	bool quit = false;
	do {

    	double value;
    	double rate;
    	unsigned int years;

		cout << endl << "Type C or Q and press enter \n\n(O) to do One time calculation \n(R) for Repeating calculation \n(Q) to Quit?" << endl;
    	cin >> menu_choice;
				 	  	
    	if (menu_choice == "Q")
    	{
		    quit = true;
			break;
	    }

    	cout << "Enter a double, the value: ";
    	cin >> value;
    	cout << endl << "Enter an annualized rate (as a percentage - for an 8 % gain enter 8): ";
    	cin >> rate;
    	cout << endl << "Enter an int , the number of years: ";
    	cin >> years;	

		if (menu_choice == "O")
		{
			double final_value = final_val(value, rate, years); 
			double to_get_free = sum_needed_for_free(rate, value);
			cout << endl << "After " << years << " years earning " << rate << "% interest a year on your original $"<< value << ", you would have a total of $" << final_value << ".";
			cout << endl << "To get this item for free every year, you would need to amass $" << to_get_free << " in today's dollars";

			double have_now = 0;
			int num_years = 0;
			while ( have_now < to_get_free)
			{
				//cout << have_now << endl;
				have_now = (have_now + value) * (1 + (rate / 100));				
				num_years++;
			}

			cout << endl << "If you saved this amount every year instead, it would take you " << num_years << " years to save up that much.";
			cout << endl << "So, after " << years << " years, you would have enough to buy " << final_value / value << " of this item instead";
		}
		else if (menu_choice == "R")
		{
			cout << endl << final_val_R(value, value, rate, years);
		}
		cin.get();  
 
		cout << endl;
	    }
	while (!quit);
}