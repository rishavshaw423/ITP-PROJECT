# ITP-PROJECT
Project for the first semester for the subject Introduction to programming
# Indian Income Tax Calculator — New Regime (FY 2024–25)

A small C program that demonstrates a backend tax calculation (FY 2024–25, new regime) with a simple command-line frontend. It applies a fixed standard deduction, computes taxable income, applies progressive slab rates, and adds cess.

This README explains how to build and run the program, how the calculation works, limitations, and includes the full source code for reference.

## Table of contents

- [Quick start](#quick-start)
- [Example run](#example-run)
- [How the calculation works](#how-the-calculation-works)
- [Implementation notes & caveats](#implementation-notes--caveats)
- [Build & run](#build--run)
- [Suggested improvements](#suggested-improvements)
- [Full source code](#full-source-code)

---

## Quick start

This program reads an annual gross income (₹) from stdin, subtracts a standard deduction of ₹50,000 to get taxable income (not below zero), computes tax using a set of progressive slabs, adds a 4% health & education cess, and prints a short breakdown.

---

## Example run

Input (user types):
```
1200000
```

Example output (approx):
```
Indian Income Tax Calculator (New Regime, FY 2024-25)
Enter your annual gross income (in ₹): 1200000

Tax Calculation Breakdown:
- Standard Deduction: ₹50,000
- Taxable Income: ₹1150000.00
- Total Tax Payable: ₹75400.00
- Effective Tax Rate: 6.28%
```

(Your output formatting may differ slightly depending on locale/printf formatting.)

---

## How the calculation works

1. Standard deduction: ₹50,000 is subtracted from gross income to get taxable income. If gross income ≤ ₹50,000, taxable income becomes zero.
2. Progressive slab calculation: the program divides taxable income into ranges (slabs), multiplying each slab portion by its corresponding rate, accumulating tax.
3. Cess: a 4% cess is applied to the computed tax (tax * 0.04).
4. Final reported tax = tax + cess.

The slab logic in the program is implemented as nested conditional blocks that apply these rates to successive portions of taxable income. See the source for the exact thresholds and rate application order.

---

## Implementation notes & caveats

- The program uses a fixed standard deduction of ₹50,000 and a cess of 4%.
- Slab thresholds and rates are implemented in code. Before relying on the program for real tax decisions, verify the slab thresholds, rates and any surcharge/changes with official sources — tax rules may change and vary by jurisdiction.
- Input validation: the program rejects negative or non-numeric input.
- Numeric types: `double` is used for money calculations which is fine for demonstration but not ideal for production financial code (consider integer paise/₹100 or a decimal/decimal128 library to avoid rounding issues).
- Readability: the slab computation is done using nested ifs and reuses a variable name (`slab5`) in two nested blocks. This is valid C (scoped declarations) but can be confusing; see Suggested improvements for a clearer design.
- Edge cases: extremely large incomes can lead to precision/overflow issues with `double`. For production-grade tax calculators, use precise decimal arithmetic or integer smallest-currency units.

---

## Build & run

Save the source to a file (e.g., `tax_calc.c`) and compile.

Linux / macOS (GCC or Clang):
```bash
gcc -O2 -o tax_calc tax_calc.c -lm
./tax_calc
```

Windows (MinGW / MSYS2):
```bash
gcc -O2 -o tax_calc.exe tax_calc.c -lm
tax_calc.exe
```

Then follow the prompt and enter the annual gross income as a number.

---

## Suggested improvements

- Replace nested-if slab logic with a data-driven approach (array of slab thresholds and rates) to make maintenance and updates easier.
- Use integer arithmetic in paise (₹ × 100) to avoid floating-point rounding issues.
- Add unit tests for sample inputs and expected outputs to catch regressions when rules change.
- Add command-line flags (e.g., `--deduction`, `--show-breakdown`, `--no-cess`) and accept CSV/batch inputs.
- Support multiple tax regimes (old / new) and toggles for surcharge calculations.
- Improve formatting (thousand separators, localized currency) and add more informative breakdown per slab.
- Add proper error handling for stdin read failures and non-numeric input.

---

## Full source code

Below is the full program source. Save it as `tax_calc.c` (or another name) and compile as shown above.

```c
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
```

---
