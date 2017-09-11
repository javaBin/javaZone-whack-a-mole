from flask import Flask, url_for, request, current_app

app = Flask(__name__, static_url_path='')

@app.route('/')
def welcome():
    return app.send_static_file('index.html')


@app.route("/api/startgame")
def start_game():
    return "Starting Game."

@app.route("/api/getscore")
def get_score():
    return "Score = "  


def has_no_empty_params(rule):
    defaults = rule.defaults if rule.defaults is not None else ()
    arguments = rule.arguments if rule.arguments is not None else ()
    return len(defaults) >= len(arguments)

@app.route("/api")
def site_map():
    links = []
    for rule in app.url_map.iter_rules():
        # Filter out rules we can't navigate to in a browser
        # and rules that require parameters
        if "GET" in rule.methods and has_no_empty_params(rule):
            url = url_for(rule.endpoint, **(rule.defaults or {}))
            links.append((url, rule.endpoint))
    # links is now a list of url, endpoint tuples
    return str(links)


if __name__ == "__main__":
    app.run()