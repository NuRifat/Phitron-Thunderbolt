from services.bank_service import BankService

service = BankService()


def main_menu():
    while True:
        print("\n1. Register\n2. Login\n3. Exit")
        choice = input("Choose: ")

        if choice == "1":
            name = input("Name: ")
            email = input("Email: ")
            password = input("Password: ")

            print("Role? (admin/manager/employee/customer)")
            role = input("Role: ")

            service.register(name, email, password, role)

        elif choice == "2":
            email = input("Email: ")
            password = input("Password: ")

            user = service.login(email, password)

            if user:
                print("✅ Login success")
                role_based_menu(user)
            else:
                print("❌ Invalid credentials")

        elif choice == "3":
            break


def role_based_menu(user):
    role = user[4]

    if role == "admin":
        admin_menu()
    elif role == "manager":
        manager_menu()
    elif role == "employee":
        employee_menu()
    else:
        customer_menu(user)


# ---------------- CUSTOMER ----------------
    
def customer_menu(user):
    account = service.get_account(user[0])

    while True:
        print("\n1.Deposit 2.Withdraw 3.Transfer 4.Balance 5.History 6.Logout")
        choice = input("Choose: ")

        if choice == "1":
            service.deposit(account[0], float(input("Amount: ")))

        elif choice == "2":
            service.withdraw(account[0], float(input("Amount: ")))

        
        elif choice == "3":
            email = input("Receiver Email: ")
            amt = float(input("Amount: "))
            service.transfer(account[0], email, amt)

        elif choice == "4":
            service.check_balance(account[0])

        elif choice == "5":
            service.transaction_history(account[0])

        elif choice == "6":
            break


# ---------------- ADMIN ----------------
def admin_menu():
    while True:
        print("\nADMIN: 1.Users 2.Delete 3.Accounts 4.Logout")
        ch = input("Choose: ")

        if ch == "1":
            service.view_all_users()

        elif ch == "2":
            uid = int(input("User ID: "))
            service.delete_user(uid)

        elif ch == "3":
            service.view_all_accounts()

        elif ch == "4":
            break


# ---------------- MANAGER ----------------
def manager_menu():
    while True:
        print("\nMANAGER: 1.Create Employee 2.View Employees 3.Logout")
        ch = input("Choose: ")

        if ch == "1":
            name = input("Name: ")
            email = input("Email: ")
            password = input("Password: ")
            service.register(name, email, password, "employee")

        elif ch == "2":
            service.view_employees()

        elif ch == "3":
            break


# ---------------- EMPLOYEE ----------------
def employee_menu():
    while True:
        print("\nEMPLOYEE: 1.View Customers 2.Deposit 3.Logout")
        ch = input("Choose: ")

        if ch == "1":
            service.view_customers()

        elif ch == "2":
            acc = int(input("Account ID: "))
            amt = float(input("Amount: "))
            service.deposit(acc, amt)

        elif ch == "3":
            break