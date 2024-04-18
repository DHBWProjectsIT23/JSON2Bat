# Format JSON
## Klasse: DataObject
Wie ist die Klasse aufgebaut?
- outputfile: std::String
- hideshell: bool
- array entries:
    - Einträge
    - "type" ENV: std::vector<std::tuple<std::string>>
        - "key" und "value"
    - "type" EXE: std::vector<std::string>
        - "command"
    - "type" PATH: std::vector<std::string>
        - "path"
- application: std::sring
