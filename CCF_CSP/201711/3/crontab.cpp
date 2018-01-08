#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#define TIME_LEN 12
#define MAX_N 20
#define MAX_EACH_LINE 100

using namespace std;

int days_of_month[] = {31, 28, 31, 30, 31, 30,
					   31, 31, 30, 31, 30, 31};

void updateDays(int *days_of_month, int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		days_of_month[1] = 29;
	}
}

struct Time
{
	int minute;
	int hour;
	int date;
	int month;
	int year;
	int day; //星期几

	void inc();
	const string format();
	bool operator==(const Time&time)
	{
		return minute == time.minute &&
			   hour == time.hour &&
			   date == time.date &&
			   month == time.month &&
			   year == time.year &&
			   day == time.day;
	}
	bool operator!=(const Time&time) {return !(*this == time);}
};

void Time::inc()
{
	minute++;
	if(minute == 60)
	{
		hour++;
		minute %= 60;
	}
	if(hour == 24)
	{
		date++;
		hour %= 24;
	}
	updateDays(days_of_month, year);
	if(date > days_of_month[month - 1])
	{
		month++;
		date = 1;
	}
	if(month > 12)
	{
		year++;
		month = 1;
	}
	day = (day + 1) % 7;
}

const string Time::format()
{
	string timeStr;
	timeStr += year;
	timeStr += (month < 10 ? "0" : "");
	timeStr += month;
	timeStr += (date < 10 ? "0" : "");
	timeStr += date;
	timeStr += (hour < 10 ? "0" : "");
	timeStr += hour;
	timeStr += (minute < 10 ? "0" : "");
	timeStr += minute;
	// timeStr = timeStr + tostring(year) + (month < 10 ? '0' : '') + string(month) + (date < 10 ? '0' : '') + string(date) +
	// 		  (hour < 10 ? '0' : '') + string(hour) + (minute < 10 ? '0' : '') + string(minute);
	return timeStr;
}

struct Task
{
	int minutes[60];
	int hours[24];
	int dates[31];
	int months[12];
	int days[7];
	char command[MAX_EACH_LINE];

	Task();
	bool match(const Time&time);
};

Task::Task()
{
	memset(minutes, -1, sizeof(minutes));
	memset(hours, -1, sizeof(hours));
	memset(dates, -1, sizeof(dates));
	memset(months, -1, sizeof(months));
	memset(days, -1, sizeof(days));
}

bool Task::match(const Time&time)
{
	for(int i = 0; i < 60; i++)
	{
		if(minutes[i] == -1) return false;
		if(minutes[i] == time.minute) break;
	}
	for(int i = 0; i < 24; i++)
	{
		if(hours[i] == -1) return false;
		if(hours[i] == time.hour) break;
	}
	for(int i = 0; i < 31; i++)
	{
		if(dates[i] == -1) return false;
		if(dates[i] == time.date) break;
	}
	for(int i = 0; i < 12; i++)
	{
		if(months[i] == -1) return false;
		if(months[i] == time.month) break;
	}
	for(int i = 0; i < 7; i++)
	{
		if(days[i] == -1) return false;
		if(days[i] == time.day) break;
	}
	return true;
}

int n;
string configs[MAX_N];
Task tasks[MAX_N];
Time start, end, cur;

void getTime(const char*timeStr, Time&time)
{
	time.year = (timeStr[0] - '0') * 1000 + (timeStr[1] - '0') * 100 + (timeStr[2] - '0') * 10 + (timeStr[3] - '0');
	time.month = (timeStr[4] - '0') * 10 + (timeStr[5] - '0');
	time.date = (timeStr[6] - '0') * 10 + (timeStr[7] - '0');
	time.hour = (timeStr[8] - '0') * 10 + (timeStr[9] - '0');
	time.hour = (timeStr[10] - '0') * 10 + (timeStr[11] - '0');
}

void getTask(const string configStr, Task&task)
{
	stringstream ss(configStr);
	char temp[MAX_EACH_LINE];
	int index;
	bool continous;

	memset(temp, 0, sizeof(temp));
	ss >> temp;
	index = 0;
	continous = false;
	for(int i = 0; i < strlen(temp);)
	{
		if(temp[0] == '*')
		{
			for(int k = 0; k < 60; k++) task.minutes[k] = k;
			break;
		}
		if(continous == false)
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && temp[j] != '-' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			if(temp[j] == '-') continous = true;
			if(j - i == 1) task.minutes[index++] = numStr[0] - '0';
			if(j - i == 2) task.minutes[index++] = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			i = j + 1;
		}
		else
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			int end;
			if(j - i == 1) end = numStr[0] - '0';
			if(j - i == 2) end = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			for(int k = task.minutes[index - 1]; k <= end; k++)
			{
				task.minutes[index++] = k;
			}
			i = j + 1;
			continous = false;
		}
	}

	memset(temp, 0, sizeof(temp));
	ss >> temp;
	index = 0;
	continous = false;
	for(int i = 0; i < strlen(temp); i++)
	{
		if(temp[0] == '*')
		{
			for(int i = 0; i < 24; i++) task.hours[i] = i;
			break;
		}
		if(continous == false)
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && temp[j] != '-' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			if(temp[j] == '-') continous = true;
			if(j - i == 1) task.hours[index++] = numStr[0] - '0';
			if(j - i == 2) task.hours[index++] = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			i = j + 1;
		}
		else
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			int end;
			if(j - i == 1) end = numStr[0] - '0';
			if(j - i == 2) end = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			for(int k = task.hours[index - 1]; k <= end; k++)
			{
				task.hours[index++] = k;
			}
			i = j + 1;
			continous = false;
		}
	}

	memset(temp, 0, sizeof(temp));
	ss >> temp;
	index = 0;
	continous = false;
	for(int i = 0; i < strlen(temp); i++)
	{
		if(temp[0] == '*')
		{
			for(int i = 0; i < 60; i++) task.dates[i] = i + 1;
			break;
		}
		if(continous == false)
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && temp[j] != '-' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			if(temp[j] == '-') continous = true;
			if(j - i == 1) task.dates[index++] = numStr[0] - '0';
			if(j - i == 2) task.dates[index++] = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			i = j + 1;
		}
		else
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			int end;
			if(j - i == 1) end = numStr[0] - '0';
			if(j - i == 2) end = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			for(int k = task.dates[index - 1]; k <= end; k++)
			{
				task.dates[index++] = k;
			}
			i = j + 1;
			continous = false;
		}
	}

	memset(temp, 0, sizeof(temp));
	ss >> temp;
	index = 0;
	continous = false;
	for(int i = 0; i < strlen(temp); i++)
	{
		if(temp[0] == '*')
		{
			for(int i = 0; i < 60; i++) task.months[i] = i + 1;
			break;
		}
		if(continous == false)
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && temp[j] != '-' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			if(temp[j] == '-') continous = true;
			if(j - i == 1) task.months[index++] = numStr[0] - '0';
			if(j - i == 2) task.months[index++] = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			i = j + 1;
		}
		else
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			int end;
			if(j - i == 1) end = numStr[0] - '0';
			if(j - i == 2) end = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			for(int k = task.months[index - 1]; k <= end; k++)
			{
				task.months[index++] = k;
			}
			i = j + 1;
			continous = false;
		}
	}

	memset(temp, 0, sizeof(temp));
	ss >> temp;
	index = 0;
	continous = false;
	for(int i = 0; i < strlen(temp); i++)
	{
		if(temp[0] == '*')
		{
			for(int i = 0; i < 60; i++) task.days[i] = i;
			break;
		}
		if(continous == false)
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && temp[j] != '-' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			if(temp[j] == '-') continous = true;
			if(j - i == 1) task.days[index++] = numStr[0] - '0';
			if(j - i == 2) task.days[index++] = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			i = j + 1;
		}
		else
		{
			char numStr[3];
			int j = i;
			while(temp[j] != ',' && j < strlen(temp))
			{
				numStr[j - i] = temp[j];
				j++;
			}
			int end;
			if(j - i == 1) end = numStr[0] - '0';
			if(j - i == 2) end = (numStr[0] - '0') * 10 + (numStr[1] - '0');
			for(int k = task.days[index - 1]; k <= end; k++)
			{
				task.days[index++] = k;
			}
			i = j + 1;
			continous = false;
		}
	}
}

int main(int argc, char const *argv[])
{
	char s[TIME_LEN + 1], t[TIME_LEN + 1];
	scanf("%d%s%s", &n, s, t);
	for(int i = 0; i < n; i++)
	{
		getline(cin, configs[i]);
	}
	getTime(s, start);
	getTime(t, end);
	cur = start;
	for(int i = 0; i < n; i++)
	{
		getTask(configs[i], tasks[i]);
	}
	while(cur != end)
	{
		for(int i = 0; i < n; i++)
		{
			if(tasks[i].match(cur))
			{
				cout << cur.format() << tasks[i].command;
			}
			if(cur != end || i != n - 1)
			{
				putchar('\n');
			}
		}
		cur.inc();
	}
	return 0;
}