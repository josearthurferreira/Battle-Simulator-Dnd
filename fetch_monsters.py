import urllib.request
import json
import os

def fetch_data(url):
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req) as response:
        return json.loads(response.read().decode())

def process_monsters():
    base_url = "https://www.dnd5eapi.co"
    monsters_index = fetch_data(base_url + "/api/monsters")
    formatted_monsters = []

    for item in monsters_index['results']:
        m_data = fetch_data(base_url + item['url'])
        
        clean_m = {
            "id": m_data['index'],
            "name": m_data['name'],
            "type": m_data['type'],
            "cr": m_data.get('challenge_rating', 0),
            "hp": m_data.get('hit_points', 0),
            "attributes": [
                m_data.get('strength', 10),
                m_data.get('dexterity', 10),
                m_data.get('constitution', 10),
                m_data.get('intelligence', 10),
                m_data.get('wisdom', 10),
                m_data.get('charisma', 10)
            ],
            "actions": [],
            "spells": []
        }

        for action in m_data.get('actions', []):
            act_data = {
                "name": action['name'],
                "desc": action['desc']
            }
            clean_m['actions'].append(act_data)

        if 'special_abilities' in m_data:
            for ability in m_data['special_abilities']:
                if 'spellcasting' in ability:
                    for spell in ability['spellcasting'].get('spells', []):
                        url_parts = spell['url'].split('/')
                        clean_m['spells'].append(url_parts[-1])

        formatted_monsters.append(clean_m)

    with open("data/monsters.json", "w", encoding="utf-8") as f:
        json.dump(formatted_monsters, f, indent=4)

os.makedirs("data", exist_ok=True)
process_monsters()