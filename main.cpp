#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "hashMap.h"

// Pseudocode for separate chaining from Discussion 12 slides used.
// https://stackoverflow.com/questions/30181600/reading-two-columns-in-csv-file-in-c for reading the CSV file
// https://stackoverflow.com/questions/42866524/convert-chronoduration-to-string-or-c-string for timing the compare function

int main()
{
    // Creates the hashmap and reads in data from the CSV file to add to it.
    hashMap map;
    std::ifstream in ("final_data_with_titles.csv");
    std::vector<std::vector<std::string>> movieData;
    std::string line;

    int count = 0;
    std::getline(in, line);
    while(std::getline(in, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> data;
        std::string value;
        while(std::getline(iss, value, ','))
        {
            data.push_back(value);
        }
        std::vector<std::string> attributes;
        attributes.push_back(data[1]);
        attributes.push_back(data[3]);
        attributes.push_back(data[2]);
        map.insert(data[4], attributes);
        count++;

        // Limits the dataset to the first 1000 entries to speed up testing, remove when ready to submit.
        if(count > 2000)
        {
            break;
        }
    }

    // Creates the render window and all the visual elements
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Letterboxd Lvrs");
    sf::Font font;
    font.loadFromFile("Lora.ttf");

    sf::Text title;
    title.setString("MOVIE MATCH MAKER");
    title.setFont(font);
    title.setCharacterSize(54);
    title.setFillColor(sf::Color::Black);
    title.setPosition(347,25);

    sf::Color background(247, 232, 199, 255);
    sf::Color textColor(255, 89, 100, 255);

    sf::Text q;
    q.setString("QUESTIONS");
    q.setFont(font);
    q.setCharacterSize(36);
    q.setFillColor(textColor);
    q.setPosition(104,155);

    sf::Text sText;
    sText.setString("SUBMIT");
    sText.setFont(font);
    sText.setCharacterSize(32);
    sText.setFillColor(sf::Color::Black);
    sText.setPosition(148,605);

    sf::Text resultTitle;
    resultTitle.setString("#1 Recommendation");
    resultTitle.setFont(font);
    resultTitle.setCharacterSize(27);
    resultTitle.setFillColor(sf::Color::Black);
    resultTitle.setPosition(508,210);

    sf::Text topResults;
    topResults.setString("TOP RESULTS");
    topResults.setFont(font);
    topResults.setCharacterSize(36);
    topResults.setFillColor(sf::Color::Black);
    topResults.setPosition(950,150);

    sf::Text topResultsText;
    topResultsText.setString("Ranking           Title            Rating");
    topResultsText.setFont(font);
    topResultsText.setCharacterSize(18);
    topResultsText.setFillColor(sf::Color::Black);
    topResultsText.setPosition(925,210);

    sf::Text numOne;
    numOne.setString("");
    numOne.setFont(font);
    numOne.setCharacterSize(18);
    numOne.setFillColor(sf::Color::Blue);
    numOne.setPosition(508,340);

    sf::Text r1;
    r1.setString("1. ");
    r1.setFont(font);
    r1.setCharacterSize(22);
    r1.setFillColor(sf::Color::Black);
    r1.setPosition(935,250);

    sf::Text r2;
    r2.setString("2. ");
    r2.setFont(font);
    r2.setCharacterSize(22);
    r2.setFillColor(sf::Color::Black);
    r2.setPosition(935,330);

    sf::Text r3;
    r3.setString("3. ");
    r3.setFont(font);
    r3.setCharacterSize(22);
    r3.setFillColor(sf::Color::Black);
    r3.setPosition(935,410);

    sf::Text r4;
    r4.setString("4. ");
    r4.setFont(font);
    r4.setCharacterSize(22);
    r4.setFillColor(sf::Color::Black);
    r4.setPosition(935,490);

    sf::Text r5;
    r5.setString("5. ");
    r5.setFont(font);
    r5.setCharacterSize(22);
    r5.setFillColor(sf::Color::Black);
    r5.setPosition(935,570);

    sf::Text q1T;
    q1T.setString("GENRE");
    q1T.setFont(font);
    q1T.setCharacterSize(20);
    q1T.setFillColor(textColor);
    q1T.setPosition(70,250);

    sf::String q1TSP = "";
    sf::Text q1TS;
    q1TS.setString(q1TSP);
    q1TS.setFont(font);
    q1TS.setCharacterSize(20);
    q1TS.setFillColor(textColor);
    q1TS.setPosition(160,250);

    sf::Text q2T;
    q2T.setString("GENRE");
    q2T.setFont(font);
    q2T.setCharacterSize(20);
    q2T.setFillColor(textColor);
    q2T.setPosition(70,310);

    sf::String q2TSP = "";
    sf::Text q2TS;
    q2TS.setString(q2TSP);
    q2TS.setFont(font);
    q2TS.setCharacterSize(20);
    q2TS.setFillColor(textColor);
    q2TS.setPosition(160,310);

    sf::Text q3T;
    q3T.setString("GENRE");
    q3T.setFont(font);
    q3T.setCharacterSize(20);
    q3T.setFillColor(textColor);
    q3T.setPosition(70,370);

    sf::String q3TSP = "";
    sf::Text q3TS;
    q3TS.setString(q3TSP);
    q3TS.setFont(font);
    q3TS.setCharacterSize(20);
    q3TS.setFillColor(textColor);
    q3TS.setPosition(160,370);

    sf::Text q4T;
    q4T.setString("LENGTH");
    q4T.setFont(font);
    q4T.setCharacterSize(20);
    q4T.setFillColor(textColor);
    q4T.setPosition(65,430);

    sf::String q4TSP = "";
    sf::Text q4TS;
    q4TS.setString(q4TSP);
    q4TS.setFont(font);
    q4TS.setCharacterSize(20);
    q4TS.setFillColor(textColor);
    q4TS.setPosition(160,430);

    sf::Text q5T;
    q5T.setString("RELEASE");
    q5T.setFont(font);
    q5T.setCharacterSize(20);
    q5T.setFillColor(textColor);
    q5T.setPosition(65,490);

    sf::String q5TSP = "";
    sf::Text q5TS;
    q5TS.setString(q5TSP);
    q5TS.setFont(font);
    q5TS.setCharacterSize(20);
    q5TS.setFillColor(textColor);
    q5TS.setPosition(160,490);

    sf::Text q6T;
    q6T.setString("RATING");
    q6T.setFont(font);
    q6T.setCharacterSize(20);
    q6T.setFillColor(textColor);
    q6T.setPosition(65,550);

    sf::String q6TSP = "";
    sf::Text q6TS;
    q6TS.setString(q6TSP);
    q6TS.setFont(font);
    q6TS.setCharacterSize(20);
    q6TS.setFillColor(textColor);
    q6TS.setPosition(160,550);

    sf::RectangleShape rectangle(sf::Vector2f(300, 525));
    rectangle.setFillColor(background);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(4);
    rectangle.setPosition(60, 138);

    sf::RectangleShape rectangle2(sf::Vector2f(300, 525));
    rectangle2.setFillColor(background);
    rectangle2.setOutlineColor(sf::Color::Black);
    rectangle2.setOutlineThickness(4);
    rectangle2.setPosition(920, 138);

    sf::RectangleShape rectangle3(sf::Vector2f(300, 325));
    rectangle3.setFillColor(background);
    rectangle3.setOutlineColor(sf::Color::Black);
    rectangle3.setOutlineThickness(4);
    rectangle3.setPosition(490, 200);

    sf::RectangleShape q1(sf::Vector2f(180, 25));
    q1.setFillColor(background);
    q1.setOutlineColor(sf::Color::Black);
    q1.setOutlineThickness(4);
    q1.setPosition(160, 250);

    sf::RectangleShape q2(sf::Vector2f(180, 25));
    q2.setFillColor(background);
    q2.setOutlineColor(sf::Color::Black);
    q2.setOutlineThickness(4);
    q2.setPosition(160, 310);

    sf::RectangleShape q3(sf::Vector2f(180, 25));
    q3.setFillColor(background);
    q3.setOutlineColor(sf::Color::Black);
    q3.setOutlineThickness(4);
    q3.setPosition(160, 370);

    sf::RectangleShape q4(sf::Vector2f(180, 25));
    q4.setFillColor(background);
    q4.setOutlineColor(sf::Color::Black);
    q4.setOutlineThickness(4);
    q4.setPosition(160, 430);

    sf::RectangleShape q5(sf::Vector2f(180, 25));
    q5.setFillColor(background);
    q5.setOutlineColor(sf::Color::Black);
    q5.setOutlineThickness(4);
    q5.setPosition(160, 490);

    sf::RectangleShape q6(sf::Vector2f(180, 25));
    q6.setFillColor(background);
    q6.setOutlineColor(sf::Color::Black);
    q6.setOutlineThickness(4);
    q6.setPosition(160, 550);

    sf::RectangleShape submit(sf::Vector2f(140, 50));
    submit.setFillColor(textColor);
    submit.setOutlineColor(sf::Color::Black);
    submit.setOutlineThickness(4);
    submit.setPosition(140, 600);

    sf::RectangleShape reset(sf::Vector2f(140, 30));
    reset.setFillColor(sf::Color::Cyan);
    reset.setOutlineColor(sf::Color::Black);
    reset.setOutlineThickness(4);
    reset.setPosition(570, 555);

    sf::Text resetText;
    resetText.setString("RESET");
    resetText.setFont(font);
    resetText.setCharacterSize(30);
    resetText.setFillColor(sf::Color::Black);
    resetText.setPosition(592,552);

    sf::RectangleShape genreOverlay(sf::Vector2f(140, 30));
    genreOverlay.setFillColor(sf::Color::Green);
    genreOverlay.setOutlineColor(sf::Color::Black);
    genreOverlay.setOutlineThickness(4);
    genreOverlay.setPosition(570, 615);

    sf::Text genreOverlayText;
    genreOverlayText.setString("GENRES");
    genreOverlayText.setFont(font);
    genreOverlayText.setCharacterSize(30);
    genreOverlayText.setFillColor(sf::Color::Black);
    genreOverlayText.setPosition(580,612);

    sf::Text genres;
    genres.setString("Action          Children\n"
                     "Adventure   Horror\n"
                     "War              Documentary\n"
                     "Western      Drama\n"
                     "Musical        Animation\n"
                     "Crime\n"
                     "Mystery\n"
                     "Thriller\n"
                     "IMAX\n"
                     "Romance\n"
                     "Sci-Fi\n"
                     "Fantasy\n"
                     "Comedy\n");
    genres.setFont(font);
    genres.setCharacterSize(30);
    genres.setFillColor(sf::Color::Black);
    genres.setPosition(20,20);

    sf::RectangleShape genreOverlayBackground(sf::Vector2f(1280, 720));
    genreOverlayBackground.setFillColor(sf::Color::Magenta);
    genreOverlayBackground.setOutlineColor(sf::Color::Black);
    genreOverlayBackground.setOutlineThickness(4);
    genreOverlayBackground.setPosition(0, 0);

    bool drawOverlay = false;

    // Runs the window and polls for clicks and mouse position to determine what happens when clicked.
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Submit button
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && sf::Mouse::getPosition(window).x > 140 && sf::Mouse::getPosition(window).x < 280
                    && sf::Mouse::getPosition(window).y > 600 && sf::Mouse::getPosition(window).y < 650)
            {
                // Times the compare function.
                auto start = std::chrono::system_clock::now();
                std::vector<std::pair<std::string, std::vector<std::string>>> results = map.compare(q6TSP, q5TSP, q4TSP);
                // If results vector is greater than 0, sorts the vector alphabetically and then adds
                // the results to each visual element on the GUI as needed.
                if(results.size() > 0)
                {
                    std::sort(results.begin(), results.end());
                    std::string resultString = "";
                    resultString += results[0].first + " ";
                    auto end = std::chrono::system_clock::now();
                    std::ostringstream out;
                    out << std::chrono::duration<double>(end-start).count() << 's';
                    std::string s = out.str();
                    numOne.setString(resultString + " \nTime Taken: " + s);

                    std::string resultString2 = "1. ";
                    resultString2 += results[0].first + "\n " + results[0].second[0];
                    r1.setString(resultString2);
                }
                if(results.size() > 1)
                {
                    std::string resultString = "2. ";
                    resultString += results[1].first + "\n " + results[1].second[0];
                    r2.setString(resultString);
                }
                if(results.size() > 2)
                {
                    std::string resultString = "3. ";
                    resultString += results[2].first + "\n " + results[2].second[0];
                    r3.setString(resultString);
                }
                if(results.size() > 3)
                {
                    std::string resultString = "4. ";
                    resultString += results[3].first + "\n " + results[3].second[0];
                    r4.setString(resultString);
                }
                if(results.size() > 4)
                {
                    std::string resultString = "5. ";
                    resultString += results[4].first + "\n " + results[4].second[0];
                    r5.setString(resultString);
                }
            }

            // Reset button
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
               && sf::Mouse::getPosition(window).x > 570 && sf::Mouse::getPosition(window).x < 710
               && sf::Mouse::getPosition(window).y > 555 && sf::Mouse::getPosition(window).y < 585)
            {
                numOne.setString("");
                q1TSP = "";
                q1TS.setString(q1TSP);
                q2TSP = "";
                q2TS.setString(q2TSP);
                q3TSP = "";
                q3TS.setString(q3TSP);
                q4TSP = "";
                q4TS.setString(q4TSP);
                q5TSP = "";
                q5TS.setString(q5TSP);
                q6TSP = "";
                q6TS.setString(q6TSP);

                r1.setString("1. ");
                r2.setString("2. ");
                r3.setString("3. ");
                r4.setString("4. ");
                r5.setString("5. ");
            }

            // Genres overlay button
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
               && sf::Mouse::getPosition(window).x > 570 && sf::Mouse::getPosition(window).x < 710
               && sf::Mouse::getPosition(window).y > 615 && sf::Mouse::getPosition(window).y < 645)
            {
                drawOverlay = !drawOverlay;
            }

            //Text entry
            if (event.type == sf::Event::TextEntered)
            {
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 250 && sf::Mouse::getPosition(window).y < 275)
                {
                    q1TSP +=event.text.unicode;
                    q1TS.setString(q1TSP);
                }
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 310 && sf::Mouse::getPosition(window).y < 335)
                {
                    q2TSP +=event.text.unicode;
                    q2TS.setString(q2TSP);
                }
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 370 && sf::Mouse::getPosition(window).y < 395)
                {
                    q3TSP +=event.text.unicode;
                    q3TS.setString(q3TSP);
                }
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 430 && sf::Mouse::getPosition(window).y < 455)
                {
                    q4TSP +=event.text.unicode;
                    q4TS.setString(q4TSP);
                }
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 490 && sf::Mouse::getPosition(window).y < 515)
                {
                    q5TSP +=event.text.unicode;
                    q5TS.setString(q5TSP);
                }
                if(sf::Mouse::getPosition(window).x > 180 && sf::Mouse::getPosition(window).x < 340
                   && sf::Mouse::getPosition(window).y > 550 && sf::Mouse::getPosition(window).y < 575)
                {
                    q6TSP +=event.text.unicode;
                    q6TS.setString(q6TSP);
                }
            }
        }

        window.clear(background);
        window.draw(title);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(submit);
        window.draw(q);
        window.draw(sText);
        window.draw(q1);
        window.draw(q1T);
        window.draw(q2);
        window.draw(q2T);
        window.draw(q3);
        window.draw(q3T);
        window.draw(q4);
        window.draw(q4T);
        window.draw(q5);
        window.draw(q5T);
        window.draw(q6);
        window.draw(q6T);
        window.draw(resultTitle);
        window.draw(topResults);
        window.draw(topResultsText);
        window.draw(r1);
        window.draw(r2);
        window.draw(r3);
        window.draw(r4);
        window.draw(r5);
        window.draw(numOne);
        window.draw(q1TS);
        window.draw(q2TS);
        window.draw(q3TS);
        window.draw(q4TS);
        window.draw(q5TS);
        window.draw(q6TS);
        window.draw(reset);
        window.draw(genreOverlay);
        window.draw(resetText);
        window.draw(genreOverlayText);
        if(drawOverlay)
        {
            window.draw(genreOverlayBackground);
            window.draw(genreOverlay);
            window.draw(genreOverlayText);
            window.draw(genres);
        }
        window.display();
    }

    return 0;
}
