from http.server import BaseHTTPRequestHandler, HTTPServer
import json
from datetime import datetime

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data)

            username = data.get('username')
            password = data.get('password')

            print(f"Received Username: {username}, Password: {password}")

            # Perform authentication logic here
            if username == "admin" and password == "password":
                self.log_success(username)
                self.send_response(200)
                self.end_headers()
                self.wfile.write(b'{"message": "Login successful"}')
            else:
                self.send_response(401)
                self.end_headers()
                self.wfile.write(b'{"message": "Invalid credentials"}')

    def log_success(self, username):
        with open("log.txt", "a") as log_file:
            log_file.write(f"{datetime.now()} - Successful login by user: {username}\nUser belongs to household 1.\nUser's last visit was 39 days ago. Allow User to shop.")

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('127.0.0.1', port)
    httpd = server_class(server_address, handler_class)
    print(f"Server running on http://127.0.0.1:{port}")
    httpd.serve_forever()

if __name__ == '__main__':
    run()
