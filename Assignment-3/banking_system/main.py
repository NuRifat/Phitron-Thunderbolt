from database.db import init_db
from ui.menu import main_menu

if __name__ == "__main__":
    init_db()
    main_menu()