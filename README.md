# Word Frequency Counter

## Project Overview

The Word Frequency Counter is an application designed to analyze and count the frequency of words in various text formats. Users can upload .txt files, or paste text directly into the application. The application provides features to sort, search, and filter word frequencies, and it saves global word frequencies for future reference.

## Features

- **File Upload:**
  - Users can upload .txt files.
  - The application extracts text from these files and counts word frequencies.

- **Text Input:**
  - Users can paste text directly into the application.
  - The application processes the pasted text for word frequency analysis.

- **Word Frequency Counting:**
  - Counts occurrences of each word in the uploaded file or pasted text.
  - Displays word frequencies in a sorted order.

- **Search Feature:**
  - Allows users to search for specific words within the counted results.

- **Filter Feature:**
  - Enables users to filter the displayed results based on specific criteria.

- **Global and Local Frequencies:**
  - Saves and maintains global and local frequencies of words across different sessions.

## Technologies Used

- **Programming Language:** C++
- **Libraries/Frameworks:**
  - **Qt:** For GUI and application management
- **Build System:** CMake

## How It Works

1. **Upload/Enter Text:**
   - Users upload a file or paste text into the application.

2. **Text Extraction:**
   - For files, the application extracts text content.

3. **Word Counting:**
   - The text is processed to count the frequency of each word.

4. **Display Results:**
   - Results are displayed in a sorted order based on frequency.
   - Users can search and filter through the results.

5. **Save Frequencies:**
   - The application saves global word frequencies for future sessions.

## Installation and Setup
Ensure CMake and Qt are installed on your system and run the `word_frequency.exe` file.
