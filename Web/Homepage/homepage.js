var quotes = [
  "You're off to great places, today is your day. Your mountain is waiting, so get on your way. - Dr. Seuss",
  "You always pass failure on the way to success. - Mickey Rooney",
  "No one is perfect - that's why pencils have erasers. - Wolfgang Riebe",
  "Winning doesn't always mean being first. Winning means you're doing better than you've done before. - Bonnie Blair",
  "You're braver than you believe, and stronger than you seem, and smarter than you think - A.A Mine",
  "It always seems impossible until it is done. - Nelson Mandela",
  "All your dreams can come true if you have the courage to pursue them - Walt Disney",
  "Keep your face to the sunshine and you cannot see a shadow. - Helen Keller",
  "The only time you fail is when you fall down and stay down - Stephen Richards",
  "You are never too old to set another goal or dream a new dream - Les Brown"
]
function quoter()
{
  let n = Math.floor(Math.random() * quotes.length);
  document.querySelector('#quotegenerator').innerHTML = quotes[n];
}
window.onload = quoter;
