import os
from flask import g, Flask
from psycopg2 import connect
import psycopg2.extras

app = Flask(__name__)

# psql lcpecommerce
def get_db():
    if not hasattr(g, 'postgres_db'):
        g.postgres_db = connect (
            host=os.getenv('DATABASE_HOST'),
            database=os.getenv('DATABASE_NAME'),
            user=os.getenv('DATABASE_USERNAME'),
            password=os.getenv('DATABASE_PASSWORD')
        )
    return g.postgres_db

# https://stackoverflow.com/questions/21158033/query-from-postgresql-using-python-as-dictionary
def db(query, args = []):
    conn = get_db()
    cursor = conn.cursor(cursor_factory=psycopg2.extras.DictCursor)
    cursor.execute(query, args)
    data = cursor.fetchall()
    cursor.close()
    return data

#https://www.postgresql.org/files/developer/concurrency.pdf
def db_insert(table, query, args = []):
    conn = get_db()
    cursor = conn.cursor()
    cursor.execute('BEGIN')
    cursor.execute(f'LOCK TABLE {table} IN SHARE ROW EXCLUSIVE MODE')
    cursor.execute(query, args)
    conn.commit()
    cursor.close()
    
@app.teardown_appcontext
def close_database(error):
    if hasattr(g, 'postgres_db'):
        g.postgres_db.close()