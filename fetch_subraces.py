import urllib.request
import json
import os

def fetch_data(url):
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req) as response:
        return json.loads(response.read().decode())

def process_subraces():
    base_url = "https://www.dnd5eapi.co"
    subraces_index = fetch_data(base_url + "/api/subraces")
    formatted_subraces = []

    for item in subraces_index['results']:
        sub_data = fetch_data(base_url + item['url'])

        ability_bonuses = [0, 0, 0, 0, 0, 0]

        for bonus in sub_data.get('ability_bonuses', []):
            attr_index = {
                "STR": 0, "DEX": 1, "CON": 2, "INT": 3, "WIS": 4, "CHA": 5
            }.get(bonus['ability_score']['index'].upper(), -1)

            if attr_index != -1:
                ability_bonuses[attr_index] = bonus['bonus']

        clean_sub = {
            "id": sub_data['index'],
            "name": sub_data['name'],
            "parent_race": sub_data['race']['index'],
            "ability_bonuses": ability_bonuses,
            "starting_proficiencies": [prof['index'] for prof in sub_data.get('starting_proficiencies', [])],
            "traits": [trait['index'] for trait in sub_data.get('racial_traits', [])]
        }
        formatted_subraces.append(clean_sub)

    with open("data/subraces.json", "w", encoding="utf-8") as f:
        json.dump(formatted_subraces, f, indent=4)

os.makedirs("data", exist_ok=True)
process_subraces()