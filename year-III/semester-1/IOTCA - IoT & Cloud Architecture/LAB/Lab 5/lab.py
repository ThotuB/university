import pyrebase

def run_auth(firebase):
    auth = firebase.auth()
    email = input('Email: ')
    password = input('Password: ')

    try:
        auth.sign_in_with_email_and_password(email, password)
        print("Signed in successfully!")
    except:
        print("Invalid email or password!")


def register(firebase):
    auth = firebase.auth()
    email = input('Email: ')
    password = input('Password: ')
    confirmPassword = input('Confirm Password: ')
    
    if password == confirmPassword:
        auth.create_user_with_email_and_password(email, password)
    else:
        print("Passwords do not match!")
        register(firebase)


def store(firebase):
    storage = firebase.storage()
    filename = input('Filename: ')
    cloud_filename = input('Cloud Filename: ')
    
    try:
        storage.child(cloud_filename).put(filename)
        print(f'Link: {storage.child(cloud_filename).get_url(None)}')
    except:
        print("Invalid filename or cloud filename!")
        store(firebase)
  
        
def download(firebase):
    storage = firebase.storage()
    cloud_filename = input('Cloud Filename: ')
    filename = input('Filename: ')
    
    try:
        storage.child(cloud_filename).download(filename)
        print(f'File downloaded to {filename}')
    except:
        print("Invalid filename or cloud filename!")
        download(firebase)


def db_set(firebase):
    db = firebase.database()
    data = {'age': 21, 'name': 'John'}
    db.child("People").child("Person").child("John").set(data)


def db_update(firebase):
    db = firebase.database()
    db.child("People").child("Person").child("John").update({'age': 22})


def db_read(firebase):
    db = firebase.database()
    people = db.child("People").child("Person").get()
    
    for person in people.each():
        print(f'{person.val()}\n{person.key()}')


def db_remove(firebase):
    db = firebase.database()
    people = db.child("People").child("Person").get()

    for person in people.each():
        db.child("People").child("Person").child(person.key()).child("age").remove()
    
    
if __name__ == '__main__':
    firebaseConfig = {
        'apiKey': "AIzaSyAklFK5QUdQH5uP2msTs5t8NaKqxDJN9A8",
        'authDomain': "iiotca-ad72f.firebaseapp.com",
        'projectId': "iiotca-ad72f",
        'databaseURL': "https://iiotca-ad72f-default-rtdb.europe-west1.firebasedatabase.app/",
        'storageBucket': "iiotca-ad72f.appspot.com",
        'messagingSenderId': "782305062296",
        'appId': "1:782305062296:web:d0aaa7882a34fecfab8fed"
    }
    firebase = pyrebase.initialize_app(firebaseConfig)
    
    db_remove(firebase)
