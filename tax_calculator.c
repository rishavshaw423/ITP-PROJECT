#include <stdio.h>
#include <stdlib.h>

// Function to calculate tax (backend logic) - FY 2024-25 slabs
double calculate_tax(double income) {
    double standard_deduction = 50000.0;
    double taxable_income = (income > standard_deduction) ? (income - standard_deduction) : 0.0;

    double tax = 0.0;

    // Slab calculations
    if (taxable_income > 300000.0) {
        double slab2 = (taxable_income > 700000.0) ? 400000.0 : (taxable_income - 300000.0);
        tax += slab2 * 0.05;

        if (taxable_income > 700000.0) {
            double slab3 = (taxable_income > 1000000.0) ? 300000.0 : (taxable_income - 700000.0);
            tax += slab3 * 0.10;

            if (taxable_income > 1000000.0) {
                double slab4 = (taxable_income > 1500000.0) ? 200000.0 : (taxable_income - 1000000.0);
                tax += slab4 * 0.15;

                if (taxable_income > 1500000.0) {
                    double slab5 = (taxable_income > 2000000.0) ? 300000.0 : (taxable_income - 1500000.0);
                    tax += slab5 * 0.20;

                    if (taxable_income > 2000000.0) {
                    double slab5 = (taxable_income > 2400000.0) ? 300000.0 : (taxable_income - 2000000.0);
                    tax += slab5 * 0.25;

                    if (taxable_income > 2400000.0) {
                        tax += (taxable_income - 2400000.0) * 0.30;
                    }
                }
            }
        }
    }

    double cess = tax * 0.04;
    return tax + cess;
}

// Main function (frontend interface)
int main() {
    double income;
    printf("Indian Income Tax Calculator (New Regime, FY 2024-25)\n");
    printf("Enter your annual gross income (in ₹): ");

    if (scanf("%lf", &income) != 1 || income < 0) {
        printf("Invalid input. Please enter a non-negative number.\n");
        return 1;
    }

    double total_tax = calculate_tax(income);
    double effective_rate = (income > 0) ? (total_tax / income) * 100 : 0;

    printf("\nTax Calculation Breakdown:\n");
    printf("- Standard Deduction: ₹50,000\n");
    printf("- Taxable Income: ₹%.2f\n", (income > 50000.0) ? (income - 50000.0) : 0.0);
    printf("- Total Tax Payable: ₹%.2f\n", total_tax);
    printf("- Effective Tax Rate: %.2f%%\n", effective_rate);

    return 0;
}
