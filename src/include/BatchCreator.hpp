/**
 * @file BatchCreator.hpp
 * @author Maximilian Rodler
 * @date 22.04.2024
 * @version
 * @brief
 * @details
 *
 * @copyright See LICENSE file
 *
 * @todo Documentation in english
 */

#include "FileData.hpp"
#include "JsonHandler.hpp"
#include <fstream>
#include <sstream>

/**
 * @class BatchCreator
 * @brief Erstellt Batch Datei
 * @details Wandelt Elemente aus JSON-Datei in Batch-Format um
 *
 * @see
 *
 */
class BatchCreator {
public:
  /**
   * @brief Initialisiert BatchCreator
   * @details
   *
   * @param filename
   *
   */
  explicit BatchCreator(std::shared_ptr<parsing::FileData> fileData);

  /** @todo Documentation */
  [[nodiscard]] std::shared_ptr<std::stringstream> getDataStream() const {
    return dataStream;
  }

private:
  std::shared_ptr<std::stringstream> dataStream;

  std::shared_ptr<parsing::FileData> fileData;

  /**
   * @brief Setzt batch Datei zusammen
   * @details Beinhaltet Aufrufe der einzelnen Komponenten der batch Datei
   *
   */
  void createBatch();

  /**
   * @brief Anfang der Batch Datei
   * @details Schreibt den Teil der Batch Datei der immer gleich ist.
   * - setzt ECHO off
   * - startet cmd.exe
   *
   */
  void writeStart() const;

  /**
   * @brief Sichtbarkeit Konsole
   * @details Zeigt bzw. versteckt Konsolenausgabe
   *
   */
  void writeHideShell() const;

  /**
   * @brief Befehle ausführen
   * @details Führt Befehle aus:
   * Zu finden unter "EXE" als "command"
   *
   */
  void writeCommands() const;

  /**
   * @brief Umgebungsvariablen setzten
   * @details Setzt Umgebungsvariablen aus "ENV" nach folgender Syntax:
   * Eintrag unter "key" = Eintrag unter "value"
   *
   */
  void writeEnvVariables() const;

  /**
   * @brief Pfade setzten
   * @details Verknüpft die unter "PATH" angegebenen Pfade mit dem Systempfad
   * Setzt Pfad
   *
   */
  void writePathVariables() const;

  /**
   * @brief Öffnet Anwednung falls gewünscht
   * @details Öffnet Anwedung, falls unter "application" gegeben
   * Wird unter dem Namen aus "outputfile" gestartet
   *
   */
  void writeApp() const;

  /**
   * @brief Ende der Batch Datei
   * @details Schreibt den teil der Batch Datei der immer gleich ist
   * - setzt ECHO OFF
   *
   */
  void writeEnd() const;
};
