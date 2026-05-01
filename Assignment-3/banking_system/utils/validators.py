import re

# ---------------- EMAIL VALIDATION ----------------
def is_valid_email(email):
    pattern = r'^[\w\.-]+@[\w\.-]+\.\w+$'
    return re.match(pattern, email)


# ---------------- NEGATIVE CHECK ----------------
def is_positive(amount):
    return amount > 0