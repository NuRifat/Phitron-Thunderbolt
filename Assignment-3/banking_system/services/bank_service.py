from database.db import get_connection
from utils.helpers import print_table
from utils.validators import is_valid_email
from utils.validators import is_positive

class BankService:

    # ---------------- AUTH ----------------
    def register(self, name, email, password, role="customer"):
        conn = get_connection()
        cursor = conn.cursor()

        # EMAIL VALIDATION
        if not is_valid_email(email):
            print("❌ Invalid email format")
            conn.close()
            return

        # DUPLICATE CHECK
        cursor.execute("SELECT id FROM users WHERE email=?", (email,))
        if cursor.fetchone():
            print("❌ Email already exists")
            conn.close()
            return

        try:
            cursor.execute(
                "INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, ?)",
                (name, email, password, role)
            )

            user_id = cursor.lastrowid

            if role == "customer":
                cursor.execute(
                    "INSERT INTO accounts (user_id, balance) VALUES (?, 0)",
                    (user_id,)
                )

            conn.commit()
            print("✅ Registration successful")

        except Exception as e:
            print("❌ Error:", e)

        finally:
            conn.close()


    def login(self, email, password):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute(
            "SELECT * FROM users WHERE email=? AND password=?",
            (email, password)
        )

        user = cursor.fetchone()
        conn.close()

        return user


    def get_account(self, user_id):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute(
            "SELECT * FROM accounts WHERE user_id=?",
            (user_id,)
        )

        acc = cursor.fetchone()
        conn.close()
        return acc

    # ---------------- CUSTOMER FEATURES ----------------

    def deposit(self, account_id, amount):
        if not is_positive(amount):
            print("❌ Amount must be positive")
            return

        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute(
            "UPDATE accounts SET balance = balance + ? WHERE id=?",
            (amount, account_id)
        )

        cursor.execute(
            "INSERT INTO transactions (account_id, type, amount) VALUES (?, 'deposit', ?)",
            (account_id, amount)
        )

        conn.commit()
        conn.close()

        print("✅ Deposit successful")


    def withdraw(self, account_id, amount):
        if not is_positive(amount):
            print("❌ Amount must be positive")
            return

        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT balance FROM accounts WHERE id=?", (account_id,))
        balance = cursor.fetchone()[0]

        if amount > balance:
            print("❌ Insufficient balance")
            conn.close()
            return

        cursor.execute(
            "UPDATE accounts SET balance = balance - ? WHERE id=?",
            (amount, account_id)
        )

        cursor.execute(
            "INSERT INTO transactions (account_id, type, amount) VALUES (?, 'withdraw', ?)",
            (account_id, amount)
        )

        conn.commit()
        conn.close()

        print("✅ Withdraw successful")


    def transfer(self, sender_account_id, receiver_email, amount):
        conn = get_connection()
        cursor = conn.cursor()

        # Get sender balance
        cursor.execute("SELECT balance FROM accounts WHERE id=?", (sender_account_id,))
        sender_balance = cursor.fetchone()

        if not sender_balance:
            print("❌ Sender account not found")
            conn.close()
            return

        sender_balance = sender_balance[0]

        if amount <= 0:
            print("❌ Amount must be positive")
            conn.close()
            return

        if amount > sender_balance:
            print("❌ Insufficient balance")
            conn.close()
            return

        # Find receiver by email
        cursor.execute("SELECT id FROM users WHERE email=?", (receiver_email,))
        receiver = cursor.fetchone()

        if not receiver:
            print("❌ Receiver not found")
            conn.close()
            return

        receiver_user_id = receiver[0]

        cursor.execute("SELECT id FROM accounts WHERE user_id=?", (receiver_user_id,))
        receiver_account = cursor.fetchone()

        if not receiver_account:
            print("❌ Receiver has no account")
            conn.close()
            return

        receiver_account_id = receiver_account[0]

        # Perform transfer
        cursor.execute(
            "UPDATE accounts SET balance = balance - ? WHERE id=?",
            (amount, sender_account_id)
        )

        cursor.execute(
            "UPDATE accounts SET balance = balance + ? WHERE id=?",
            (amount, receiver_account_id)
        )

        cursor.execute(
            "INSERT INTO transactions (account_id, type, amount) VALUES (?, 'transfer_out', ?)",
            (sender_account_id, amount)
        )

        cursor.execute(
            "INSERT INTO transactions (account_id, type, amount) VALUES (?, 'transfer_in', ?)",
            (receiver_account_id, amount)
        )

        conn.commit()
        conn.close()

        print("✅ Transfer successful")

    def check_balance(self, account_id):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT balance FROM accounts WHERE id=?", (account_id,))
        balance = cursor.fetchone()[0]

        conn.close()
        print("💰 Balance:", balance)


    def transaction_history(self, account_id):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("""
            SELECT type, amount, date
            FROM transactions
            WHERE account_id=?
            ORDER BY date DESC
        """, (account_id,))

        rows = cursor.fetchall()
        conn.close()

        if not rows:
            print("📭 No transactions found")
            return

        print("\n================ TRANSACTIONS ================")
        print("TYPE        | AMOUNT     | DATE")
        print("--------------------------------------------")

        for r in rows:
            t_type = r[0].ljust(10)
            amount = str(r[1]).ljust(10)
            date = r[2]
            print(f"{t_type} | {amount} | {date}")

        print("============================================\n")

    # ---------------- ADMIN ----------------

    def view_all_users(self):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT id, name, email, role FROM users")
        for u in cursor.fetchall():
            print(u)

        conn.close()

    def view_all_users(self):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT id, name, email, role FROM users")
        rows = cursor.fetchall()
        conn.close()

        headers = ["ID", "Name", "Email", "Role"]
        print_table(headers, rows)


    def delete_user(self, user_id):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("DELETE FROM users WHERE id=?", (user_id,))
        conn.commit()
        conn.close()

        print("✅ User deleted")


    def view_all_accounts(self):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT id, user_id, balance FROM accounts")
        rows = cursor.fetchall()
        conn.close()

        headers = ["Account ID", "User ID", "Balance"]
        print_table(headers, rows)

    # ---------------- MANAGER ----------------

    def view_employees(self):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT id, name, email FROM users WHERE role='employee'")
        rows = cursor.fetchall()
        conn.close()

        headers = ["ID", "Name", "Email"]
        print_table(headers, rows)

    # ---------------- EMPLOYEE ----------------

    def view_customers(self):
        conn = get_connection()
        cursor = conn.cursor()

        cursor.execute("SELECT id, name, email FROM users WHERE role='customer'")
        rows = cursor.fetchall()
        conn.close()

        headers = ["ID", "Name", "Email"]
        print_table(headers, rows)