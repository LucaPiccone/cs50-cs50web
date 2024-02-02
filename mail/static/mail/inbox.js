/*
Title: Mail
Author: Luca Piccone
Description: A Single Page e-mail service provider.

Special Thanks to OpenAI's ChatGPT (https://www.openai.com/chatgpt).
*/

document.addEventListener('DOMContentLoaded', function() {
  // Declare some variables
  emails_view = document.querySelector('#emails-view') 
  compose_view = document.querySelector('#compose-view')
  email_recipients = document.querySelector('#compose-recipients')
  email_subject = document.querySelector('#compose-subject')
  email_body = document.querySelector('#compose-body')
  user = document.querySelector('#user').value

  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'));
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'));
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'));
  document.querySelector('#compose').addEventListener('click', compose_email);

  // By default, load the inbox
  load_mailbox('inbox');

  // Send email request
  document.querySelector('#compose-form').onsubmit = function() {
    sendEmail(email_recipients.value, email_subject.value, email_body.value);
    return false;
  }

});


function compose_email() {

  // Show compose view and hide other views
  emails_view.style.display = 'none';
  compose_view.style.display = 'block';

  // Clear out composition fields
  email_recipients.value = '';
  email_subject.value = '';
  email_body.value = '';

  //Send email request is at the top
}


function load_mailbox(mailbox) {
  
  // Show the mailbox and hide other views
  emails_view.style.display = 'block';
  compose_view.style.display = 'none';

  // Show the mailbox name
  emails_view.innerHTML = `<h3>${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>`;

  load_emails(mailbox);
}


function sendEmail(recipients, subject, body) {
  fetch('/emails', {
    method: 'POST',
    body: JSON.stringify({
        recipients: recipients,
        subject: subject,
        body: body
    })
  })
  .then(response => response.json())
  .then(data => {
      // Print result
      //console.log(data);
      if (data.error) {
        compose_email()
      }
      else {
        load_mailbox('sent')
      }
  });
}


function reply(sender, recipients, subject, timestamp, body, doubleReplyCheck) {
  compose_email()
  // variables declared at the top of file.
  email_recipients.value = sender;

  // Check if its the first reply
  if (!subject.toLowerCase().startsWith("re:")) {
    email_subject.value = `Re: ${subject}`;
    if (doubleReplyCheck === false) {
      email_body.value = `On ${timestamp} ${sender} wrote: ${body} \n \n`;
    }
    else {
      email_body.value = `On ${timestamp} ${recipients} wrote: ${body} \n \n`;
    }
  } else if (body.indexOf('\n \n') !== -1) {
    email_subject.value = subject
    var index = body.lastIndexOf('\n');
    if (doubleReplyCheck === false) {
      // append the time and the sender to the last email sent after the \n \n.
      email_body.value = `${body.substring(0, index + 1)} On ${timestamp} ${sender} wrote: ${body.substring(index + 1)} \n \n`
    } 
    else {
      email_body.value = `${body.substring(0, index + 1)} On ${timestamp} ${recipients} wrote: ${body.substring(index + 1)} \n \n`
    }
  }
  // else {
  //   email_subject.value = subject
  //   email_body.value = body
  // }
}


function load_emails(mailbox) {
  fetch(`/emails/${mailbox}`)
  .then(response => response.json())
  .then(emails => {
      // Print emails
      //console.log(emails);

      // Create a load_emails component.
      emails.forEach(function(email) {
        //console.log(email.body)
        
        const div = document.createElement('div');
        div.classList.add('emailSnippetContainer');

          const child_div_1 = document.createElement('div');
          child_div_1.classList.add('emailSnippetChild1');
          div.append(child_div_1);

            const child_div_1_left = document.createElement('div');
            child_div_1_left.classList.add('emailSnippetChild1_left');
            child_div_1_left.innerHTML = email.sender ;
            child_div_1.append(child_div_1_left);

            const child_div_1_right = document.createElement('div');
            child_div_1_right.classList.add('emailSnippetChild1_right');
            child_div_1_right.innerHTML = email.timestamp;
            child_div_1.append(child_div_1_right);

          const child_div_2 = document.createElement('div');
          child_div_2.classList.add('emailSnippetChild2');
          child_div_2.innerHTML = email.subject;
          div.append(child_div_2);

        emails_view.append(div);

        div.addEventListener('click', function() {
          readEmail(email.id)
        })

        if (email.read === true & mailbox !== 'sent') {
          div.style.background = 'lightgrey'
        }
        else {
          div.style.background = 'white'
        }

      });

  });
}


function load_email(email_id) {

  fetch(`/emails/${email_id}`)
  .then(response => response.json())
  .then(email => {
      console.log(email);

      emails_view.innerHTML = "";

      const div = document.createElement('div');
      div.classList.add("emailContainer")

        const child_div_1 = document.createElement('div');
        child_div_1.classList.add('emailSnippetChild1');
        div.append(child_div_1);

          const child_div_1_left = document.createElement('div');
          child_div_1_left.classList.add('emailSnippetChild1_left');
          child_div_1_left.innerHTML = email.sender ;
          child_div_1.append(child_div_1_left);

          const child_div_1_right = document.createElement('div');
          child_div_1_right.classList.add('emailSnippetChild1_right');
          child_div_1_right.innerHTML = email.timestamp;
          child_div_1.append(child_div_1_right);

        const child_div_2 = document.createElement('div');
        child_div_2.classList.add('emailSnippetChild2');
        child_div_2.innerHTML = email.subject;
        div.append(child_div_2);

        const child_div_3 = document.createElement('div');
        child_div_3.classList.add('emailSubject');
        child_div_3.innerHTML = `To: ${email.recipients.join(", ")}`;
        div.append(child_div_3);

        const sectionBreak = document.createElement('hr');
        div.append(sectionBreak);

        const child_div_4 = document.createElement('div');
        child_div_4.classList.add('emailBody');
        child_div_4.innerHTML = email.body.replace(/\n/g, '<br>');
        div.append(child_div_4)

        const child_div_5 = document.createElement('div');
        child_div_5.classList.add('emailButtons');
        div.append(child_div_5)

          const child_div_5_left = document.createElement('button');
          child_div_5_left.classList.add('emailLeftButton', 'btn', 'btn-sm', 'btn-outline-primary');
          child_div_5_left.innerHTML = "Reply"
          child_div_5.append(child_div_5_left)

          const child_div_5_middle = document.createElement('button');
          child_div_5_middle.classList.add('emailMiddleButton', 'btn', 'btn-sm', 'btn-outline-primary');
          child_div_5.append(child_div_5_middle)

          const child_div_5_right = document.createElement('button');
          child_div_5_right.classList.add('emailRightButton', 'btn', 'btn-sm', 'btn-outline-primary');
          child_div_5_right.innerHTML = "Unread";
          child_div_5.append(child_div_5_right);

          // Handles the reply button. (send email is called function (event listener at the top))
        child_div_5_left.addEventListener('click', function() {
          // Handles the case where the email is being viewed from the sent mailbox.
          if (email.sender === user & !email.recipients.includes(user)) {
            reply(email.recipients, email.sender, email.subject, email.timestamp, email.body, true)
          } else {
            reply(email.sender, email.recipients, email.subject, email.timestamp, email.body, false)
          }
        })

        // Handles archive button 
        if (email.sender === user & !email.recipients.includes(user)) {
          child_div_5_middle.style.display = 'none';
          child_div_5_right.style.display = 'none';

        } else if (email.archived === false) {
          child_div_5_middle.innerHTML = 'Archive Email';
          child_div_5_middle.addEventListener('click', function() {
            archiveEmail(email.id)
          })
        } else {
          child_div_5_middle.innerHTML = 'Unarchive Email';
          child_div_5_middle.addEventListener('click', function() {
            unArchiveEmail(email.id)
          })
        }

        // Handles Unread button
        if (email.read === true) {
          child_div_5_right.addEventListener('click', function() {
            unReadEmail(email.id)
            child_div_5_right.disabled = true;
          }) 
        }

        emails_view.append(div);

  });

}


function archiveEmail(email_id) {

  fetch(`/emails/${email_id}`, {
    method: 'PUT',
    body: JSON.stringify({
        archived: true
    })
  })
  .then(response => {
    load_mailbox('inbox');
  });

}


function unArchiveEmail(email_id) {
  fetch(`/emails/${email_id}`, {
    method: 'PUT',
    body: JSON.stringify({
        archived: false
    })
  })
  .then(response => {
    load_mailbox('inbox');
  });
}


function readEmail(email_id) {
  fetch(`/emails/${email_id}`, {
    method: 'PUT',
    body: JSON.stringify({
        read: true
    })
  })
  .then(response => {
    load_email(email_id);
  })
}


function unReadEmail(email_id) {
  fetch(`/emails/${email_id}`, {
    method: 'PUT',
    body: JSON.stringify({
        read: false
    })
  })
}